package javatst.tst;

public class Test {
    private transient String key;//在写入文件或网络传输过程中会变成NULL或0丢失掉，保证安全性
    private final int Ten=10;
    protected String account;
    static int count=0;
    public volatile boolean myflag=true;
    public Test()
    {
        account="hello";
        count++;
        myflag=!myflag;
    }
    public static int getCount()
    {
        return count;
    }
    public void setKey(String str)
    {
        this.key=str;
    }
    public String getKey()
    {
        return key;
    }
    public String getAccount()
    {
        return account;
    }
}
