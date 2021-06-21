import com.fazecast.jSerialComm.SerialPort;

public class Alumne {
    public static final int SNAKE_STEP_DELAY = 200; // Time to wait between snake steps in milliseconds
    public static final int TIME_WAIT_MS = 100; // Time to wait before calling "getInput()" in milliseconds

    public static void sendScore(Snake snake, SerialPort serialPort) {
        char score = (char) snake.getScore();

        // Write your code here
        serialPort.
    }

    public static void getInput(Snake snake, SerialPort serialPort) {

        if(serialPort.bytesAvailable())
        switch () {
            case 2:
            snake.up(); // Moves the snake up
            snake.down(); // Moves the snake down
            snake.left(); // Moves the snake left
            snake.right(); // Moves the snake right
        }

        // Write your code here
    }

    public static void gameOver(Snake snake, SerialPort serialPort) {
        // Write your code here
    }
}
