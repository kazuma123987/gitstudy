package javatst;

import java.util.*;

import java.time.LocalDate;//年月日
import java.time.LocalTime;//时分秒
import java.time.LocalDateTime;//LocalDate+LocalTime

public class Main {
    public static boolean flag=false;
    public static void main(String[] args) {
        Timer timer1 = new Timer();// 定时器1
        Timer timer2 = new Timer();// 定时器2
        TimerTask task1 = new TimerTask() // 定时任务
        {
            @Override
            public void run() {
                System.out.println(LocalDateTime.now().toString());
            }
        };
        TimerTask task2 = new TimerTask() {
            @Override
            public void run() {
              flag=true;
              timer1.cancel();
              timer2.cancel();  
            }
        };
        while (!flag) {
            timer1.schedule(task1, 0, 100);
            timer2.schedule(task2, 1000);
        }
    }
}