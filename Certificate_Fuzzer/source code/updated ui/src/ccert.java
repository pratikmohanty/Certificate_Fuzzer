import java.awt.*;
import javax.swing.*;
import com.jgoodies.forms.factories.*;
import com.jgoodies.forms.layout.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.URI;
import java.nio.file.Paths;
import javax.swing.*;
import com.jgoodies.forms.factories.*;
import com.jgoodies.forms.layout.*;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextField;

/*
 * Created by JFormDesigner on Sat Mar 26 23:46:51 IST 2016
 */



/**
 * @author chandrasekar balachandran
 */
public class ccert extends JFrame {
    public ccert() {
        initComponents();
    }

    private JFileChooser fileChooser1;
    private JFileChooser fileChooser2;

    private void initComponents() {
        // JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
        // Generated using JFormDesigner Evaluation license - chandrasekar balachandran
        label1 = new JLabel();
        textField1 = new JTextField();
        label2 = new JLabel();
        textField8 = new JTextField();
        label3 = new JLabel();
        textField2 = new JTextField();
        label4 = new JLabel();
        textField3 = new JTextField();
        label5 = new JLabel();
        textField4 = new JTextField();
        label6 = new JLabel();
        textField5 = new JTextField();
        label7 = new JLabel();
        textField6 = new JTextField();
        label8 = new JLabel();
        textField7 = new JTextField();
        label9 = new JLabel();
        textField9 = new JTextField();
        label10 = new JLabel();
        textField10 = new JTextField();
        label11 = new JLabel();
        textField11 = new JTextField();
        label12 = new JLabel();
        button3 = new JButton();
        textField12 = new JTextField();
        button2 = new JButton();

        //======== this ========
        setTitle("CITRIX RVCE CUSTOM CERTIFICATE CREATOR");
        Container contentPane = getContentPane();
        contentPane.setLayout(new FormLayout(
            "9*(default, $lcgap), default",
            "15*(default, $lgap), default"));

        //---- label1 ----
        label1.setText("VERSION NUMBER");
        contentPane.add(label1, CC.xy(5, 5));
        contentPane.add(textField1, CC.xywh(7, 5, 9, 1));

        //---- label2 ----
        label2.setText("SERIAL NUMBER");
        contentPane.add(label2, CC.xy(5, 7));
        contentPane.add(textField8, CC.xywh(7, 7, 9, 1));

        //---- label3 ----
        label3.setText("SIGNATURE ALGORITHM ID");
        contentPane.add(label3, CC.xy(5, 9));
        contentPane.add(textField2, CC.xywh(7, 9, 9, 1));

        //---- label4 ----
        label4.setText("ISSUER ORGANIZATION (O)");
        contentPane.add(label4, CC.xy(5, 11));
        contentPane.add(textField3, CC.xywh(7, 11, 9, 1));

        //---- label5 ----

        label5.setText("ISSUER CN");
        contentPane.add(label5, CC.xy(5, 13));
        contentPane.add(textField4, CC.xywh(7, 13, 9, 1));

        //---- label6 ----
        label6.setText("Netscape Comment (v3)");
        contentPane.add(label6, CC.xy(5, 15));
        contentPane.add(textField5, CC.xywh(7, 15, 9, 1));

        //---- label7 ----
        label7.setText("SUBJECT O");
        contentPane.add(label7, CC.xy(5, 17));
        contentPane.add(textField6, CC.xywh(7, 17, 9, 1));

        //---- label8 ----
        label8.setText("SUBJECT CN");
        contentPane.add(label8, CC.xy(5, 19));
        contentPane.add(textField7, CC.xywh(7, 19, 9, 1));

        //---- label9 ----
        label9.setText("VALIDATION PERIOD (NOT BEFORE)");
        contentPane.add(label9, CC.xy(5, 21));
        contentPane.add(textField9, CC.xywh(7, 21, 9, 1));

        //---- label10 ----
        label10.setText("VALIDATION PERIOD (NOT AFTER)");
        contentPane.add(label10, CC.xy(5, 23));
        contentPane.add(textField10, CC.xywh(7, 23, 9, 1));

        //---- label11 ----
        label11.setText("CERTIFICATE SIGNATURE");
        contentPane.add(label11, CC.xy(5, 25));
        contentPane.add(textField11, CC.xywh(7, 25, 9, 1));

        //---- label12 ----
        label12.setText("OUTPUT DESTINATION");
        contentPane.add(label12, CC.xy(5, 29));

        //---- button3 ----
        button3.setText("BROWSE");
        contentPane.add(button3, CC.xy(7, 29));
        fileChooser1 = new JFileChooser();
        fileChooser1.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        button3.addActionListener(ay -> {
            if (fileChooser1.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                textField12.setText(fileChooser1.getSelectedFile().getAbsolutePath());
            }
        });
        contentPane.add(textField12, CC.xywh(9, 29, 7, 1));

        //---- button2 ----
        button2.setText("CREATE");
        contentPane.add(button2, CC.xy(9, 31));
        pack();
        setLocationRelativeTo(getOwner());

        button2.addActionListener(ay -> {

            String version =textField1.getText();
            String serial=textField8.getText();
            String iso=textField3.getText();
            String icn=textField4.getText();
            String nc=textField5.getText();
            String so=textField6.getText();
            String scn=textField7.getText();
            String vpnb=textField9.getText();
            String vpna=textField10.getText();
            String op=textField12.getText();

            try {

                final URI uri;
                final URI exe;
                final URI srl;
                uri = jarpack.getJarURI();
                exe = jarpack.getFile(uri,"individual");
                Runtime.getRuntime().exec("chmod +x "+String.valueOf(Paths.get(exe).toFile()));

                ProcessBuilder processBuilder = new ProcessBuilder(String.valueOf(Paths.get(exe).toFile()), "-v", version, "-s", serial, "-i", iso,"-c",icn,"-n",nc,"-z",so,"-y",scn,"-x",vpnb,"-w",vpna,"-o",op);
                processBuilder.redirectErrorStream(true);
                processBuilder.inheritIO();
                //port to all systems
              //  processBuilder.directory(new File("/home/bharath/citrix"));
                Process p = processBuilder.start();

//                BufferedReader reader =
//                        new BufferedReader(new InputStreamReader(p.getInputStream()));
//                StringBuilder builder = new StringBuilder();
//                String line = null;
//                while ( (line = reader.readLine()) != null) {
//                    builder.append(line);
//                    builder.append(System.getProperty("line.separator"));
//                }
//                String result = builder.toString();
//
//                System.out.println(result);



            } catch (Exception e) {
                e.printStackTrace();
            }

        });
        // JFormDesigner - End of component initialization  //GEN-END:initComponents
    }

    // JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
    // Generated using JFormDesigner Evaluation license - chandrasekar balachandran
    private JLabel label1;
    private JTextField textField1;
    private JLabel label2;
    private JTextField textField8;
    private JLabel label3;
    private JTextField textField2;
    private JLabel label4;
    private JTextField textField3;
    private JLabel label5;
    private JTextField textField4;
    private JLabel label6;
    private JTextField textField5;
    private JLabel label7;
    private JTextField textField6;
    private JLabel label8;
    private JTextField textField7;
    private JLabel label9;
    private JTextField textField9;
    private JLabel label10;
    private JTextField textField10;
    private JLabel label11;
    private JTextField textField11;
    private JLabel label12;
    private JButton button3;
    private JTextField textField12;
    private JButton button2;
    // JFormDesigner - End of variables declaration  //GEN-END:variables
}
