import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Snake extends JPanel {
    private JPanel board;
    private JButton[] snakeBodyPart;
    private JTextArea nameViewer;
    private JTextArea scoreViewer;
    private JTextArea timeViewer;

    // Constants
    private final int BOARD_WIDTH = 600;
    private final int BOARD_HEIGHT = 600;
    private final int SCORE_BOARD_HEIGHT = 20;
    private final int SNAKE_LENGTH_DEFAULT = 4;
    private final int SNAKE_BODY_PART_SQUARE = 20;
    private final Point INIT_POINT = new Point(SNAKE_BODY_PART_SQUARE * 5, SNAKE_BODY_PART_SQUARE * 5);

    // Others values
    private int totalBodyPart;
    private int directionX;
    private int directionY;
    private int score;
    private String name = "Unknown";
    private int time = 0;
    private boolean isRunning;
    private final Random random = new Random();
    private OnEventListener eventListener;

    Snake() {
        init();
    }

    public void init() {
        setPreferredSize(new Dimension(BOARD_WIDTH, BOARD_HEIGHT + SCORE_BOARD_HEIGHT));

        JPanel scorePanel = new JPanel();
        nameViewer = new JTextArea("Name: " + name);
        nameViewer.setEnabled(false);
        nameViewer.setBackground(Color.BLACK);
        scoreViewer = new JTextArea("Score: " + score);
        scoreViewer.setEnabled(false);
        scoreViewer.setBackground(Color.BLACK);
        timeViewer = new JTextArea("Time: " + time);
        timeViewer.setEnabled(false);
        timeViewer.setBackground(Color.BLACK);

        board = new JPanel();
        board.setLayout(null);
        board.setBounds(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
        board.setBackground(Color.WHITE);
        scorePanel.setLayout(new GridLayout(0, 3));
        scorePanel.setBounds(0, BOARD_HEIGHT, BOARD_WIDTH, SCORE_BOARD_HEIGHT);
        scorePanel.setBackground(Color.RED);
        scorePanel.add(nameViewer);
        scorePanel.add(scoreViewer);
        scorePanel.add(timeViewer);

        setLayout(null);
        add(board);
        add(scorePanel);
        setVisible(true);
    }

    public void resetDefaultValues() {
        snakeBodyPart = new JButton[2000];
        totalBodyPart = SNAKE_LENGTH_DEFAULT;
        directionX = SNAKE_BODY_PART_SQUARE;
        directionY = 0;
        score = 0;
    }

    /**
     * This method is responsible to initialize the snake with four body part.
     */
    public void createInitSnake() {
        // Location of the snake's head.
        int x = (int) INIT_POINT.getX();
        int y = (int) INIT_POINT.getY();

        // Initially the snake has three body part.
        for (int i = 0; i < totalBodyPart; i++) {
            snakeBodyPart[i] = new JButton();
            snakeBodyPart[i].setBounds(x, y, SNAKE_BODY_PART_SQUARE, SNAKE_BODY_PART_SQUARE);
            snakeBodyPart[i].setBackground(Color.GRAY);
            board.add(snakeBodyPart[i]);
            // Set location of the next body part of the snake.
            x = x - SNAKE_BODY_PART_SQUARE;
        }

        // Create food.
        createFood();
    }

    /**
     * This method is responsible to create food of a snake.
     * The most last part of this snake is treated as a food, which has not become a body part of the snake yet.
     * This food will be the body part if and only if when snake head will touch it.
     */
    void createFood() {
        int randomX = SNAKE_BODY_PART_SQUARE * random.nextInt(BOARD_WIDTH / SNAKE_BODY_PART_SQUARE);
        int randomY = SNAKE_BODY_PART_SQUARE * random.nextInt(BOARD_HEIGHT / SNAKE_BODY_PART_SQUARE);

        snakeBodyPart[totalBodyPart] = new JButton();
        snakeBodyPart[totalBodyPart].setEnabled(false);
        snakeBodyPart[totalBodyPart].setBounds(randomX, randomY, SNAKE_BODY_PART_SQUARE, SNAKE_BODY_PART_SQUARE);
        snakeBodyPart[totalBodyPart].setBackground(Color.RED);
        board.add(snakeBodyPart[totalBodyPart]);

        totalBodyPart++;
    }

    /**
     * Process next step of the snake.
     * And decide what should be done.
     */
    void processNextStep() {
        boolean isBorderTouched = false;

        // Generate new location of snake head.
        int newHeadLocX = (int) snakeBodyPart[0].getLocation().getX() + directionX;
        int newHeadLocY = (int) snakeBodyPart[0].getLocation().getY() + directionY;

        // Most last part of the snake is food.
        int foodLocX = (int) snakeBodyPart[totalBodyPart - 1].getLocation().getX();
        int foodLocY = (int) snakeBodyPart[totalBodyPart - 1].getLocation().getY();

        // Check does snake cross the border of the board?
        if (newHeadLocX > BOARD_WIDTH - SNAKE_BODY_PART_SQUARE) {
            newHeadLocX = 0;
            isBorderTouched = true;
        } else if (newHeadLocX < 0) {
            newHeadLocX = BOARD_WIDTH - SNAKE_BODY_PART_SQUARE;
            isBorderTouched = true;
        } else if (newHeadLocY > BOARD_HEIGHT - SNAKE_BODY_PART_SQUARE) {
            newHeadLocY = 0;
            isBorderTouched = true;
        } else if (newHeadLocY < 0) {
            newHeadLocY = BOARD_HEIGHT - SNAKE_BODY_PART_SQUARE;
            isBorderTouched = true;
        }

        // Check has snake touched the food?
        if (newHeadLocX == foodLocX && newHeadLocY == foodLocY) {
            // Set score.
            score += 5;
            if (eventListener != null) eventListener.onScoreUpdated(score);
            scoreViewer.setText("Score: " + score);

            snakeBodyPart[totalBodyPart - 1].setBackground(Color.GRAY);

            // Create new food.
            createFood();
        }

        // Check is game over?
        if (isGameOver(isBorderTouched, newHeadLocX, newHeadLocY)) {
            scoreViewer.setText("GAME OVER! Score: " + score);
            if (eventListener != null) eventListener.onGameOver(score);
            isRunning = false;
            return;
        } else {
            // Move the whole snake body to forword.
            moveSnakeForword(newHeadLocX, newHeadLocY);
        }

        nameViewer.setText("Name: " + name);
        timeViewer.setText("Time: " + time);

        board.repaint();
    }

    /**
     * This method is responsible to detect is game over or not?
     * Game should be over while snake is touched by any maze or by itself.
     * If any one want to add new type just declare new GAME_TYPE enum value and put logic in this method.
     *
     * @param isBorderTouched
     * @param headLocX
     * @param headLocY
     * @return
     */
    private boolean isGameOver(boolean isBorderTouched, int headLocX, int headLocY) {
        if (isBorderTouched) {
            return true;
        }

        for (int i = SNAKE_LENGTH_DEFAULT; i < totalBodyPart - 2; i++) {
            Point partLoc = snakeBodyPart[i].getLocation();
            if (partLoc.equals(new Point(headLocX, headLocY))) return true;
        }

        return false;
    }

    /**
     * Every body part should be placed to location of the front part.
     * For example if part:0(100,150) , part: 1(90, 150), part:2(80,150) and new head location (110,150) then,
     * Location of part:2 should be (80,150) to (90,150), part:1 will be (90,150) to (100,150) and part:3 will be (100,150) to (110,150)
     * This movement process should be start from the last part to first part.
     * We must avoid the food that means most last body part of the snake.
     * Notice that we write (totalBodyPart - 2) instead of (totalBodyPart - 1).
     * (totalBodyPart - 1) means food and (totalBodyPart - 2) means tail.
     *
     * @param headLocX
     * @param headLocY
     */
    public void moveSnakeForword(int headLocX, int headLocY) {
        for (int i = totalBodyPart - 2; i > 0; i--) {
            Point frontBodyPartPoint = snakeBodyPart[i - 1].getLocation();
            snakeBodyPart[i].setLocation(frontBodyPartPoint);
        }
        snakeBodyPart[0].setBounds(headLocX, headLocY, SNAKE_BODY_PART_SQUARE, SNAKE_BODY_PART_SQUARE);
    }

    public void up() {
        directionX = 0;
        directionY = -SNAKE_BODY_PART_SQUARE; // means snake move from down to up by 10 pixel
    }

    public void down() {
        directionX = 0;
        directionY = +SNAKE_BODY_PART_SQUARE; // means snake move from left to right by 10 pixel
    }

    public void left() {
        directionX = -SNAKE_BODY_PART_SQUARE; // means snake move right to left by 10 pixel
        directionY = 0;
    }

    public void right() {
        directionX = +SNAKE_BODY_PART_SQUARE; // means snake move from left to right by 10 pixel
        directionY = 0;
    }

    public void setOnEventListener(OnEventListener listener) {
        this.eventListener = listener;
    }

    private void createThread() {
        new Thread(() -> {
            while (true) {
                if (isRunning) {
                    // Process what should be next step of the snake.
                    processNextStep();
                    try {
                        Thread.sleep(Alumne.SNAKE_STEP_DELAY);
                    } catch (InterruptedException ignored) {
                    }
                }
            }
        }).start();
    }

    public void startGame() {
        //initialize all variables.
        resetDefaultValues();
        // initialize GUI.
        init();
        // Create Initial body of a snake.
        createInitSnake();
        // Initialize Thread.
        isRunning = true;
        createThread();
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setTime(int time) {
        this.time = time;
    }

    public int getScore() {
        return score;
    }

    public interface OnEventListener {
        void onGameOver(int score);
        void onScoreUpdated(int score);
    }
}
