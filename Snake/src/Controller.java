import com.fazecast.jSerialComm.SerialPort;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

public class Controller extends JPanel {
    private static final Integer[] STANDARD_BAUDRATES = {/*110, 300, 600, 1200, 2400, 4800, */9600/*, 14400, 19200, 38400, 57600, 115200, 128000, 256000*/};

    private final JComboBox<SerialPort> portsComboBox;
    private final JComboBox<Integer> baudRate;

    private Snake snake;
    private boolean isConnected;
    private SerialPort[] availablePorts;
    private SerialPort selectedPort;

    public Controller() {
        this.portsComboBox = new JComboBox<>();
        this.baudRate = new JComboBox<>(STANDARD_BAUDRATES);

        JButton connectButton = new JButton("Connect!");
        connectButton.addActionListener(e -> {
            //connectToPort(null);
            SerialPort selectedPort = (SerialPort) portsComboBox.getSelectedItem();
            for (SerialPort sp : availablePorts) {
                if (sp.getSystemPortName().equals(selectedPort.getSystemPortName())) {
                    connectToPort(sp);
                    System.out.println("Connected!");
                    break;
                }
            }
        });

        JButton refreshButton = new JButton("Refresh ports");
        refreshButton.addActionListener(e -> updatePorts());

        this.isConnected = false;

        setLayout(new FlowLayout());
        add(portsComboBox);
        add(baudRate);
        add(connectButton);
        add(refreshButton);

        updatePorts();
    }

    private void bindSnake(Snake snake) {
        this.snake = snake;
        snake.setOnEventListener(new Snake.OnEventListener() {
            @Override
            public void onGameOver(int score) {
                if (isConnected) Alumne.gameOver(snake, selectedPort);
                JOptionPane.showMessageDialog(new JFrame(), "Your score was: " + snake.getScore() + ". Thanks for playing! The game will exit in 10 seconds.");
                try {
                    Thread.sleep(10000);
                    System.exit(0);
                } catch (InterruptedException ignored) {
                }
            }

            @Override
            public void onScoreUpdated(int score) {
                sendScore();
            }
        });
        configureKeyBindings();
    }

    private void updatePorts() {
        availablePorts = SerialPort.getCommPorts();
        portsComboBox.setModel(new DefaultComboBoxModel<>(availablePorts));
        portsComboBox.setEnabled(availablePorts.length > 0);
    }

    private void connectToPort(SerialPort port) {
        if (port == null) {
            JFrame f = new JFrame("Snake");
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.setResizable(false);
            f.setLayout(new BorderLayout());

            final Snake snake = new Snake();
            bindSnake(snake);
            snake.startGame();

            f.add(snake, BorderLayout.CENTER);
            f.pack();
            f.setLocationRelativeTo(null);
            f.setVisible(true);

            new Thread(() -> {
                while (true) {
                    try {
                        getInput();
                        Thread.sleep(Alumne.TIME_WAIT_MS);
                    } catch (InterruptedException ignored) {
                    }
                }
            }).start();
            return;
        }

        if (port.isOpen()) {
            System.out.println("\"" + port.getSystemPortName() + "\" is already open!");
            return;
        } else {
            port.setBaudRate(STANDARD_BAUDRATES[baudRate.getSelectedIndex()]);
            selectedPort = port;
            isConnected = true;
            port.openPort();

            JFrame f = new JFrame("Snake");
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.setResizable(false);
            f.setLayout(new BorderLayout());
            f.setIconImage(new ImageIcon("icon.png").getImage());

            final Snake snake = new Snake();
            bindSnake(snake);

            f.add(snake, BorderLayout.CENTER);
            f.pack();
            f.setLocationRelativeTo(null);
            f.setVisible(true);

            new Thread(() -> {
                while (true) {
                    try {
                        getInput();
                        Thread.sleep(Alumne.TIME_WAIT_MS);
                    } catch (InterruptedException ignored) {
                    }
                }
            }).start();
        }

        if (!port.openPort()) {
            System.out.println("Error while opening \"" + port.getSystemPortName() + "\"!");
        }
    }

    private void getInput() {
        if (isConnected) Alumne.getInput(snake, selectedPort);
    }

    private void configureKeyBindings() {
        InputMap im = snake.getInputMap();
        ActionMap am = snake.getActionMap();

        im.put(KeyStroke.getKeyStroke(KeyEvent.VK_UP, 0, false), "MOVE_UP");
        im.put(KeyStroke.getKeyStroke(KeyEvent.VK_DOWN, 0, false), "MOVE_DOWN");
        im.put(KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0, false), "MOVE_LEFT");
        im.put(KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0, false), "MOVE_RIGHT");

        am.put("MOVE_UP", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                snake.up();
            }
        });

        am.put("MOVE_DOWN", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                snake.down();
            }
        });

        am.put("MOVE_LEFT", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                snake.left();
            }
        });

        am.put("MOVE_RIGHT", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                snake.right();
            }
        });
    }

    public void sendScore() {
        if (isConnected) Alumne.sendScore(snake, selectedPort);
    }
}
