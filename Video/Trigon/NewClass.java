import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class NewClass extends Canvas {

    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;
    
    public static void main(String[] args) throws Exception {
        JFrame frame_one = new JFrame();
        frame_one.setSize(WIDTH, HEIGHT);
        frame_one.setResizable(true);
        frame_one.add(new NewClass());
        frame_one.setLocationRelativeTo(null);
        frame_one.setVisible(true);
    }

    @Override
    public void paint(Graphics g) {
        try {
            super.paint(g);
            g.clearRect(0, 0, this.getWidth(), this.getHeight());
            BufferedImage bi = ImageIO.read(new File("C:\\jo\\1.png"));
            int[] pixel;
            int matchcountxpurple = 0;
            int matchcountypurple = 0;
            int matchcountxred = 0;
            int matchcountyred = 0;
            int matchcountxgreen = 0;
            int matchcountygreen = 0;
            
            int maximumredrow = 0;
            int maximumredrowvalue = 0;
            int maximumredcol = 0;
            int maximumredcolvalue = 0;
            int maximumpurplerow = 0;
            int maximumpurplerowvalue = 0;
            int maximumpurplecol = 0;
            int maximumpurplecolvalue = 0;
            int maximumgreenrow = 0;
            int maximumgreenrowvalue = 0;
            int maximumgreencol = 0;
            int maximumgreencolvalue = 0;
            
            for (int y = 0; y < bi.getHeight(); y++) {
                for (int x = 0; x < bi.getWidth(); x++) {
                    pixel = bi.getRaster().getPixel(x, y, new int[4]);
                    g.setColor(new Color(pixel[0], pixel[1], pixel[2]));
                    g.drawLine(x, y, x, y);
                }
            }

            for (int y = 0; y < bi.getHeight(); y++) {
                for (int x = 0; x < bi.getWidth(); x++) {
                    pixel = bi.getRaster().getPixel(x, y, new int[4]);
                    if ((pixel[0] == 128) && (pixel[1] == 0) && (pixel[2] == 0)) {
                        matchcountxred++;
                    }
                    if ((pixel[0] == 0) && (pixel[1] == 128) && (pixel[2] == 128)) {
                        matchcountxgreen++;
                    }
                    if ((pixel[0] == 255) && (pixel[1] == 0) && (pixel[2] == 255)) {
                        matchcountxpurple++;
                    }
                }

                if (matchcountxred > maximumredrowvalue) {
                    maximumredrow = y;
                    maximumredrowvalue = matchcountxred;
                }
                if (matchcountxgreen > maximumgreenrowvalue) {
                    maximumgreenrow = y;
                    maximumgreenrowvalue = matchcountxgreen;
                }
                if (matchcountxpurple > maximumpurplerowvalue) {
                    maximumpurplerow = y;
                    maximumpurplerowvalue = matchcountxpurple;
                }
                if (matchcountxred < matchcountxgreen) {
                    if (matchcountxgreen != 0) {
                        g.setColor(new Color(0, 128, 128));
                        g.drawLine(bi.getWidth(), y, bi.getWidth() + matchcountxgreen, y);
                        matchcountxgreen = 0;
                    }
                    if (matchcountxred != 0) {
                        g.setColor(new Color(128, 0, 0));
                        g.drawLine(bi.getWidth(), y, bi.getWidth() + matchcountxred, y);
                        matchcountxred = 0;
                    }
                } else {
                    if (matchcountxred != 0) {
                        g.setColor(new Color(128, 0, 0));
                        g.drawLine(bi.getWidth(), y, bi.getWidth() + matchcountxred, y);
                        matchcountxred = 0;
                    }
                    if (matchcountxgreen != 0) {
                        g.setColor(new Color(0, 128, 128));
                        g.drawLine(bi.getWidth(), y, bi.getWidth() + matchcountxgreen, y);
                        matchcountxgreen = 0;
                    }
                }
            }

            for (int x = 0; x < bi.getWidth(); x++) {
                for (int y = 0; y < bi.getHeight(); y++) {
                    pixel = bi.getRaster().getPixel(x, y, new int[4]);
                    if ((pixel[0] == 128) && (pixel[1] == 0) && (pixel[2] == 0)) {
                        matchcountyred++;
                    }
                    if ((pixel[0] == 0) && (pixel[1] == 128) && (pixel[2] == 128)) {
                        matchcountygreen++;
                    }
                    if ((pixel[0] == 255) && (pixel[1] == 0) && (pixel[2] == 255)) {
                        matchcountypurple++;
                    }
                }

                if (matchcountyred > maximumredcolvalue) {
                    maximumredcol = x;
                    maximumredcolvalue = matchcountyred;
                }
                if (matchcountygreen > maximumgreencolvalue) {
                    maximumgreencol = x;
                    maximumgreencolvalue = matchcountygreen;
                }
                if (matchcountypurple > maximumpurplecolvalue) {
                    maximumpurplecol = x;
                    maximumpurplecolvalue = matchcountypurple;
                }
                if (matchcountyred < matchcountygreen) {
                    if (matchcountygreen != 0) {
                        g.setColor(new Color(0, 128, 128));
                        g.drawLine(x, bi.getHeight(), x, bi.getHeight() + matchcountygreen);
                        matchcountygreen = 0;
                    }
                    if (matchcountyred != 0) {
                        g.setColor(new Color(128, 0, 0));
                        g.drawLine(x, bi.getHeight(), x, bi.getHeight() + matchcountyred);
                        matchcountyred = 0;
                    }
                } else {
                    if (matchcountyred != 0) {
                        g.setColor(new Color(128, 0, 0));
                        g.drawLine(x, bi.getHeight(), x, bi.getHeight() + matchcountyred);
                        matchcountyred = 0;
                    }
                    if (matchcountygreen != 0) {
                        g.setColor(new Color(0, 128, 128));
                        g.drawLine(x, bi.getHeight(), x, bi.getHeight() + matchcountygreen);
                        matchcountygreen = 0;
                    }
                }
            }
            System.out.println("maximumredrow " + maximumredrow);
            System.out.println("maximumredrowvalue " + maximumredrowvalue);
            System.out.println("maximumredcol " + maximumredcol);
            System.out.println("maximumredcolvalue " + maximumredcolvalue);
            System.out.println("maximumpurplerow " + maximumpurplerow);
            System.out.println("maximumpurplerowvalue " + maximumpurplerowvalue);
            System.out.println("maximumpurplecol " + maximumpurplecol);
            System.out.println("maximumpurplecolvalue " + maximumpurplecolvalue);
            System.out.println("maximumgreenrow " + maximumgreenrow);
            System.out.println("maximumgreenrowvalue " + maximumgreenrowvalue);
            System.out.println("maximumgreencol " + maximumgreencol);
            System.out.println("maximumgreencolvalue " + maximumgreencolvalue);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
