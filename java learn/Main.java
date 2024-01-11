package javatst;
public class Main {
    public static void main(String[] args) {
        Integer a = 5;
        Integer b = 10;

        System.out.println("交换前：");
        System.out.println("a = " + a); // 输出：a = 5
        System.out.println("b = " + b); // 输出：b = 10

        swapNumbers(a, b);

        System.out.println("交换后：");
        System.out.println("a = " + a); // 输出：a = 10
        System.out.println("b = " + b); // 输出：b = 5
    }

    private static void swapNumbers(Integer x, Integer y) {
        Integer temp = x;
        x = y;
        y = temp;
    }
}