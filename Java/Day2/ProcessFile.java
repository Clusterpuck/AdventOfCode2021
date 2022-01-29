import java.util.*;
import java.io.*;


public class ProcessFile
{

    public static void main( String[] args )
    {
        String fileName = args[0];
        System.out.println( "Opening file named " + fileName );
        readFile( fileName );
    }

    public static void readFile( String fileName )
    {
        int [] depthArray = {0, 0, 0};
        //Indicates the x and y coordinate magnitudes of position
        //For part 2, it is now aim x and y
        String line;
        FileInputStream fileStream = null;
        InputStreamReader rdr;
        BufferedReader bufRdr;

        try
        {
            fileStream = new FileInputStream( fileName );
            rdr = new InputStreamReader( fileStream );
            bufRdr = new BufferedReader( rdr );
            line = bufRdr.readLine();
            if( line == null )
            {
                System.out.println( "The file is empty" );
            }
            else
            {
                while( line != null )
                {
                    movePosition( depthArray, line );
                    line = bufRdr.readLine();
                }
                fileStream.close();
            }
        }
        catch( IOException e )
        {
            if( fileStream != null )
            {
                try
                {
                    fileStream.close();
                }
                catch( IOException e2 )
                { }
            }
            System.out.println( "Error in fileprocessing: " + e.getMessage() );
        }
        System.out.println( "The final position is: " + depthArray[1] +
                            " , " + depthArray[2] + "\nGiving distance of: " +
                            depthArray[1]*depthArray[2] );
    }

    public static void movePosition( int[] depthArray, String line )
    {
        String[] lineSplit = line.split( " " );
        int magnitude = Integer.parseInt( lineSplit[1] );
        switch ( lineSplit[0] )
        {
            case "forward":
            {
                depthArray[1] += magnitude;
                depthArray[2] += magnitude*depthArray[0];
                break;
            }
            case "down":
            {
                depthArray[0] += magnitude;
                break;
            }
            case "up":
            {
                depthArray[0] -= magnitude;
                break;
            }
            default:
            {
                System.out.println( "Non standard direction found" );
            }
        }
    }


}
