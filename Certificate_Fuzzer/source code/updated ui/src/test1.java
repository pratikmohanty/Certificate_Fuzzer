import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.nio.file.Paths;
import java.util.*;
import javax.swing.*;
import com.jgoodies.forms.factories.*;
import com.jgoodies.forms.layout.*;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextField;

/**
 * @author chandrasekar bala
 */
public class test1 extends JFrame {
    String cert = "";
    String pem = "";
    public int ratio, num;

    public test1() {

        initComponents();
    }

    private JFileChooser fileChooser1;
    private JFileChooser fileChooser2;
    private JFileChooser fileChooser3;
    private JFileChooser fileChooser4;

    private void initComponents() {
        label1 = new JLabel();
        progressBar1 = new JProgressBar();
        label2 = new JLabel();
        textField3 = new JTextField();
        button7 = new JButton();
        label6 = new JLabel();
        textField4 = new JTextField();
        button8 = new JButton();
        label3 = new JLabel();
        comboBox1 = new JComboBox();
        label4 = new JLabel();
        spinner1 = new JSpinner();
        label5 = new JLabel();
        comboBox2 = new JComboBox();
        label7 = new JLabel();
        textField5 = new JTextField();
        button9 = new JButton();
        button10 = new JButton();
        button1 = new JButton();
        button2 = new JButton();

        //======== this ========
        setTitle("CFUZZ RVCE CSE");
        setMinimumSize(new Dimension(49, 69));
        Container contentPane = getContentPane();
        contentPane.setLayout(new FormLayout(
                "10*(default, $lcgap), default",
                "12*(default, $lgap), default"));

        //---- label1 ----
        label1.setText("PROGRESS");
        label1.setHorizontalAlignment(SwingConstants.RIGHT);
        contentPane.add(label1, CC.xy(5, 3));
        contentPane.add(progressBar1, CC.xywh(7, 3, 9, 1));

        //---- label2 ----
        label2.setText("Select Base File");
        contentPane.add(label2, CC.xy(5, 7));
        contentPane.add(textField3, CC.xywh(7, 7, 7, 1));

        //---- button7 ----
        button7.setText("Browse");
        fileChooser1 = new JFileChooser();
        button7.addActionListener(ax -> {
            if (fileChooser1.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                textField3.setText(fileChooser1.getSelectedFile().getAbsolutePath());
            }
        });
        contentPane.add(button7, CC.xywh(15, 7, 5, 1));

        //---- label6 ----
        label6.setText("Select Key File");
        contentPane.add(label6, CC.xy(5, 9));
        contentPane.add(textField4, CC.xywh(7, 9, 7, 1));

        //---- button8 ----
        button8.setText("Browse");
        fileChooser2 = new JFileChooser();
        button8.addActionListener(ay -> {
            if (fileChooser2.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                textField4.setText(fileChooser2.getSelectedFile().getAbsolutePath());
            }
        });
        contentPane.add(button8, CC.xywh(15, 9, 5, 1));

        //---- label3 ----
        label3.setText("SET FUZZ LEVEL");
        contentPane.add(label3, CC.xy(5, 11));
        contentPane.add(comboBox1, CC.xywh(7, 11, 7, 1));

        //---- label4 ----
        label4.setText("SET NUMBER OF FILES");
        contentPane.add(label4, CC.xy(5, 13));
        contentPane.add(spinner1, CC.xywh(7, 13, 7, 1));

        //---- label5 ----
        label5.setText("SET FIELD");
        contentPane.add(label5, CC.xy(5, 15));
        contentPane.add(comboBox2, CC.xywh(7, 15, 7, 1));

        //---- label7 ----
        label7.setText("Output Destination");
        contentPane.add(label7, CC.xy(5, 17));
        contentPane.add(textField5, CC.xywh(7, 17, 7, 1));

        //---- button9 ----
        button9.setText("Browse");
        fileChooser3 = new JFileChooser();
        fileChooser3.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        button9.addActionListener(ay -> {
            if (fileChooser3.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                textField5.setText(fileChooser3.getSelectedFile().getAbsolutePath());
            }
        });
        contentPane.add(button9, CC.xywh(15, 17, 5, 1));

        //---- button10 ----
        button10.setText("CREATE CUSTOM");
        button10.addActionListener(az -> SwingUtilities.invokeLater(() -> {
            ccert GUI2 = new ccert();
            GUI2.setVisible(true);
        }));

        contentPane.add(button10, CC.xy(5, 21));

        //---- button1 ----
        button1.setText("START FUZZING");
        contentPane.add(button1, CC.xy(11, 21));

        //---- button2 ----
        button2.setText("TERMINATE");
        contentPane.add(button2, CC.xy(15, 21));
        pack();
        setLocationRelativeTo(getOwner());

        comboBox1.addItem("Low");
        comboBox1.addItem("Medium");
        comboBox1.addItem("High");
        comboBox1.addItem("Extreme");
        comboBox2.addItem("Serial Number");
        comboBox2.addItem("Version");
        comboBox2.addItem("Issuer,Subject - O");
        comboBox2.addItem("Issuer,Subject - CN");
        comboBox2.addItem("Netscape comment (v3)");
        comboBox2.addItem("All");

// set dimensions
//
//        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
//
//        setSize(screenSize.width - 1300, screenSize.height - 700);
        setLocationRelativeTo(null);    // center on screen

        progressBar1.setValue(0);
        progressBar1.setStringPainted(true);
        button1.addActionListener(ae -> {
            System.out.println("Started fuzzing");

            progressBar1.setValue(0);
            progressBar1.setStringPainted(true);

            cert = textField3.getText();
            pem = textField4.getText();

            String fuzzingLevel = comboBox1.getSelectedItem().toString();
            System.out.println(fuzzingLevel);
            ratio = 1;
            if (fuzzingLevel.equals("Low"))
                ratio = 1;
            else if (fuzzingLevel.equals("Medium"))
                ratio = 2;
            else if (fuzzingLevel.equals("High"))
                ratio = 3;
            else if (fuzzingLevel.equals("Extreme"))
                ratio = 4;


             String privkey=pem;
            String opdir=textField5.getText();
            int field=0;
//            comboBox2.addItem("Serial Number");
//            comboBox2.addItem("Version");
//            comboBox2.addItem("Issuer,Subject - O");
//            comboBox2.addItem("Issuer,Subject - CN");
//            comboBox2.addItem("Netscape comment (v3)");
//            comboBox2.addItem("All");
            String field_=comboBox2.getSelectedItem().toString();
            if(field_.equals("Version"))
                field=1;
            else if(field_.equals("Serial Number"))
                field=2;
            else if(field_.equals("Issuer,Subject - O"))
                field=3;
            else if(field_.equals("Issuer,Subject - CN"))
                field=4;
            else if(field_.equals("Netscape comment (v3)"))
                field=5;
            else if(field_.equals("All"))
                field=6;


            //privkey=privkey.substring(privkey.lastIndexOf("/") + 1).trim();
           // cert=cert.substring(cert.lastIndexOf("/")+1).trim();

            num = (Integer) spinner1.getValue();
            System.out.println(num);
            progressBar1.setMaximum(num);

            try {

                final URI uri;
                final URI exe;
                final URI srl;
                final URI deb;
                uri = jarpack.getJarURI();
                exe = jarpack.getFile(uri, "a.out");
                srl = jarpack.getFile(uri,"serial.srl");

                System.out.println(exe);
                System.out.println(srl);

                File directory =new File("/usr/bin");
                File[] fileList=directory.listFiles();
                int flag=0;
                for(File f:fileList)
                {
                    if(f.isFile())
                    {
                        if(f.getName().equals("zzuf")) {
                            flag=1;
                            break;
                        }
                    }

                }
                if(flag==0)
                {
                    deb=jarpack.getFile(uri,"cfuzz.deb");
                    Runtime.getRuntime().exec("sudo dpkg -i "+String.valueOf(Paths.get(deb).toFile()));
                }



                Runtime.getRuntime().exec("mv "+String.valueOf(Paths.get(srl).toFile())+" /tmp/serial.srl");
                Runtime.getRuntime().exec("chmod +x "+String.valueOf(Paths.get(exe).toFile()));
                ProcessBuilder processBuilder = new ProcessBuilder(String.valueOf(Paths.get(exe).toFile()), "-c", cert, "-r", String.valueOf(ratio), "-n", String.valueOf(num),"-k",privkey,"-o",opdir,"-f",String.valueOf(field));
//                processBuilder.directory(new File("/tmp"));
                processBuilder.redirectErrorStream(true);
                processBuilder.inheritIO();
            //    processBuilder.directory(new File("/home/bharath/citrix"));
                Process p = processBuilder.start();
                System.out.println(processBuilder.command());
                InputStreamConsumer stdout;
                stdout = new InputStreamConsumer(p.getInputStream(), progressBar1, button2, num);
                stdout.execute();
                button2.addActionListener(ae1 -> {
                    System.out.println("Stopped fuzzing");
                    p.destroy();
                    stdout.cancel(true);
                });
//                p.waitFor();
                System.out.println("Done.");
                progressBar1.setValue(0);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });

    }


    public static void main(String[] args) {

        javax.swing.SwingUtilities.invokeLater(() -> {
            test1 GUI = new test1();
            GUI.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            GUI.setVisible(true);

        });
    }

    private JLabel label1;
    private JProgressBar progressBar1;
    private JLabel label2;
    private JTextField textField3;
    private JButton button7;
    private JLabel label6;
    private JTextField textField4;
    private JButton button8;
    private JLabel label3;
    private JComboBox comboBox1;
    private JLabel label4;
    private JSpinner spinner1;
    private JLabel label5;
    private JComboBox comboBox2;
    private JButton button1;
    private JButton button2;

    private JLabel label7;
    private JTextField textField5;
    private JButton button9;
    private JButton button10;

    public static class InputStreamConsumer extends SwingWorker<Void, Integer> {

        private InputStream is;
        private JProgressBar text;
        private Integer num;
        private JButton button;
        int i = 0;

        public InputStreamConsumer(InputStream is, JProgressBar jProgressBar, JButton button2, int num) {
            this.is = is;
            this.text = jProgressBar;
            this.num = num;

            this.button = button2;

        }

        @Override
        protected Void doInBackground() throws Exception {
            try {
                int value = -1;
                while ((value = is.read()) != -1) {
                    System.out.print((char) value);
                    publish(i);
                }
            } catch (IOException exp) {
                exp.printStackTrace();
            }
            return null;
        }

        @Override
        protected void process(java.util.List<Integer> chunks) {
            i++;
            text.setValue(i);
            System.out.println(i);
//           label.setText("Loading " + i + " of " + max);
        }

        @Override
        protected void done() {
            text.setValue(num);
        }


    }

}