def min_moves(s: str) -> int:
    b_count = 0  # 记录已经遇到的黄豆（b）的数量
    move_steps = 0  # 记录总的移动步数
    
    # 遍历字符串
    for char in s:
        if char == 'b':
            b_count += 1  # 每遇到一个黄豆，增加计数
        elif char == 'a':
            move_steps += b_count  # 每遇到一个红豆，移动步数增加前面所有黄豆的数量
    
    return move_steps

# 测试
s = input("请输入豆子序列: ")
print(min_moves(s))