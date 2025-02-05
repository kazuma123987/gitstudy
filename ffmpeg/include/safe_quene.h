#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

//=== 线程安全队列模板 ===
template <typename T>
class SafeQueue
{
public:
    SafeQueue(size_t max_size = 1024) : max_size_(max_size) {}

    bool push(T &&item, int timeout_ms = 0)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (timeout_ms > 0)
        {
            if (!not_full_.wait_for(lock, std::chrono::milliseconds(timeout_ms),
                                    [this]
                                    { return queue_.size() < max_size_; }))
            {
                return false;
            }
        }
        else
        {
            not_full_.wait(lock, [this]
                           { return queue_.size() < max_size_; });
        }

        queue_.emplace(std::forward<T>(item)); // 完美转发
        not_empty_.notify_one();
        return true;
    }

    bool pop(T &item, int timeout_ms = 0)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (timeout_ms > 0)
        {
            if (!not_empty_.wait_for(lock, std::chrono::milliseconds(timeout_ms),
                                     [this]
                                     { return !queue_.empty(); }))
            {
                return false;
            }
        }
        else
        {
            not_empty_.wait(lock, [this]
                            { return !queue_.empty(); });
        }

        item = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return true;
    }

    // 新增非阻塞尝试弹出方法
    bool try_pop(T &item)
    {
        std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
        if (!lock.owns_lock() || queue_.empty())
        {
            return false;
        }

        item = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    std::queue<T> queue_;
    size_t max_size_;
};