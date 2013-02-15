/**
 * Sample program for image processing in Java.
 * by Takashi Michikawa
 */
import java.io.*;
import java.awt.Color;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;

public class ImageProcessingSample {
        private BufferedImage _inputImage; 
        private BufferedImage _outputImage;
	
	public ImageProcessingSample(final String filename) throws IOException {
		this._inputImage = ImageIO.read(new File ( filename ) );
		
		final int width  = this._inputImage.getWidth();
		final int height = this._inputImage.getHeight();
		this._outputImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		
		return;
	}
	
	public boolean compute() {
		final int width  = this._inputImage.getWidth();
		final int height = this._inputImage.getHeight();
		for( int y = 0 ; y < height; y++) {
			for( int x = 0 ; x < width ; x++) {
				final Color c = new Color(this._inputImage.getRGB(x,y));
				
				final int r = 255 - c.getRed();
				final int g = 255 - c.getGreen();
				final int b = 255 - c.getBlue();
				
				final Color nc = new Color (r, g, b);
				this._outputImage.setRGB(x, y, nc.getRGB());
			}
		}
		return true;
	}
	
	public void writeImage(final String filename ) throws IOException {
		ImageIO.write(this._outputImage, "jpeg", new File(filename));
		return;
	}
	
	public static void main ( String[] args ) throws IOException {
		if( args.length < 2 ) {
			System.out.println("Error. Insufficient arguments.");
			System.out.println("Usage : java ImageProcessingSample input.bmp output.jpg");
			return;
		}
		try {
			ImageProcessingSample sample = new ImageProcessingSample ( args[0] ) ;
			sample.compute();
			sample.writeImage(args[1]);
			
		} catch ( java.lang.Exception e) {
			e.printStackTrace();
		}
		return;
	}
}