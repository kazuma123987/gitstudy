package javatst;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        String text1 = "3.1441415.15155.515.345";
        String text2= " 你好 世界\n";
        //^表示从哪里开始,如果不加^,Matcher.find()方法会持续搜寻相对应的字符串(可以尝试去掉^)，\d匹配一个数字
        //？表示前面括号的内容是可以选的，可以匹配\\d+(\\.\\d+)或\\d+
        //这里\\d+表示匹配可匹配多位数
        String regex1 = "^\\d+(\\.\\d+)?";
        String regex2="世界";//字符串只会输出"世界"
        Pattern pattern1 = Pattern.compile(regex1);
        Pattern pattern2 = Pattern.compile(regex2);
        Matcher matcher1 = pattern1.matcher(text1);
        Matcher matcher2 = pattern2.matcher(text2);
        
        while (matcher1.find()) {
            System.out.println("Match: " + text1.substring(matcher1.start(), matcher1.end()));//start()和end()方法传的是字符串的序号
        }
        while (matcher2.find()) {
            System.out.println("Match: "+matcher2.group());//group()方法可以实现上述substring()的结果
        }
    }
}