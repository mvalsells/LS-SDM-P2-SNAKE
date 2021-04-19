import com.fazecast.jSerialComm.SerialPort;

public class Alumne {
    public static final int SNAKE_STEP_DELAY = 150; // Time to wait between snake steps in milliseconds
    public static final int TIME_WAIT_MS = 100; // Time to wait before calling "getInput()" in milliseconds

    public static void sendScore(Snake snake, SerialPort serialPort) {
        char score = snake.getScore();

        // Write your code here
    }

    public static void getInput(Snake snake, SerialPort serialPort) {
        /* Example code:
           snake.startGame(); // Starts the game
           snake.up(); // Moves the snake up
           snake.down(); // Moves the snake down
           snake.left(); // Moves the snake left
           snake.right(); // Moves the snake right
           snake.setName("Bad Bunny"); // Sets the name to display on the screen
           snake.setTime(69); // Sets the time to display on the screen
         */

        // Write your code here
    }

    public static void gameOver(Snake snake, SerialPort serialPort) {
        // Write your code here
    }
}
