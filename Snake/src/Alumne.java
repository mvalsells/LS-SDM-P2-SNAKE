import com.fazecast.jSerialComm.SerialPort;

public class Alumne {
    public static final int SNAKE_STEP_DELAY = 350; // Time to wait between snake steps in milliseconds
    public static final int TIME_WAIT_MS = 100; // Time to wait before calling "getInput()" in milliseconds
    private static boolean  gameStarted = false;
    private static int playingTime;
    private static StringBuilder sb = new StringBuilder();

    public static void sendScore(Snake snake, SerialPort serialPort) {
        // Write your code here
        String score = String.valueOf(snake.getScore());
        char[] data = new char[3];
        char[] chararray = score.toCharArray();

        if(score.length() == 1){
            data[0] = '0';
            data[1] = '0';
            data[2] = chararray[0];
        }else if(score.length() == 2){
            data[0] = '0';
            data[1] = chararray[0];
            data[2] = chararray[1];
        }else if(score.length() == 3){
            data[0] = chararray[0];
            data[1] = chararray[1];
            data[2] = chararray[2];
        }

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
        if (!gameStarted) {
            if ((char) b != 13){
                sb.append((char)b);
                return;
            } else {
                snake.startGame();
                snake.setName(sb.toString());
                playingTime = 0;
                gameStarted = true;
            }
        }
        //System.out.print("clicat: " + b + "");
        switch (b){
            case 2:
                snake.up();
                //System.out.println("up");
                break;
            case 8:
                snake.down();
               // System.out.println("down");
                break;
            case 4:
                snake.left();
                //System.out.println("left");
                break;
            case 6:
                snake.right();
                break;
            case 12:
                snake.setTime(++playingTime);//++time per no anar un segon atrassat
                //System.out.println("time++");
        }
    }

    public static void gameOver(Snake snake, SerialPort serialPort) {
        // Write your code here
        //envia caracter final de joc
        byte scoreToSend = (byte)snake.getScore();
        byte[] data = {'X',scoreToSend};
        serialPort.writeBytes(data, 2);
        gameStarted = false;
    }
}
