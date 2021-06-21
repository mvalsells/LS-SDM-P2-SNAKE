import com.fazecast.jSerialComm.SerialPort;

public class Alumne {
    public static final int SNAKE_STEP_DELAY = 200; // Time to wait between snake steps in milliseconds
    public static final int TIME_WAIT_MS = 100; // Time to wait before calling "getInput()" in milliseconds
    private static boolean  gameStarted = false;
    private static int playingTime;

    public static void sendScore(Snake snake, SerialPort serialPort) {
        // Write your code here
        String score = String.valueOf(snake.getScore());
        char[] data = score.toCharArray();
        byte[] data2 = {(byte)data[0], (byte)data[1], (byte)data[2]};

        serialPort.writeBytes(data2, 3);
    }

    public static void getInput(Snake snake, SerialPort serialPort) {
        if (serialPort.bytesAvailable()<1){
            return;
        }

        byte[] data = new byte[1];
        serialPort.readBytes(data,1);
        byte b = data[0];
        StringBuilder sb = new StringBuilder();
        if (!gameStarted) {
            if ((char) b !='\0'){
                sb.append((char)b);
                return;
            } else {
                snake.startGame();
                snake.setName(sb.toString());
                playingTime = 0;
                gameStarted = true;
            }
        }

        switch (b){
            case 2:
                snake.up();
                break;
            case 8:
                snake.down();
                break;
            case 4:
                snake.left();
                break;
            case 6:
                snake.right();
                break;
            case 12:
                snake.setTime(playingTime++);
        }
    }

    public static void gameOver(Snake snake, SerialPort serialPort) {
        // Write your code here
        //envia caracter final de joc
        byte[] writebuffer = new byte[serialPort.bytesAwaitingWrite()];
        serialPort.writeBytes(writebuffer, serialPort.bytesAvailable(), (long)'X');

        byte[] data = {'X',(byte)snake.getScore()};
        serialPort.writeBytes(data, 2);
        gameStarted = false;
    }
}
