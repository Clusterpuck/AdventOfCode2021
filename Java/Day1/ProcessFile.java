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
        int [] depthArray;
        int lineNum = 0;
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
                    line = bufRdr.readLine();
                    ++lineNum;
                }
                System.out.println( "File has " + lineNum + " lines" );
                fileStream.close();
                recordFileData( fileName, lineNum );
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
    }

    public static void recordFileData( String fileName, int pLineNum )
    {
        FileInputStream fileStream = null;
        InputStreamReader rdr;
        BufferedReader bufRdr;
        int[] depthArray = new int[pLineNum];
        try
        {
            fileStream = new FileInputStream( fileName );
            bufRdr = new BufferedReader( new InputStreamReader( fileStream ) );
            for( int i = 0; i < pLineNum; i++ )
            {
                depthArray[i] = Integer.parseInt( bufRdr.readLine() );
            }
            fileStream.close();
        }
        catch( Exception e )
        {
            System.out.println( "Found an error on the second pass" );
        }

        increaseNum( depthArray, pLineNum );
    }

    public static void increaseNum( int[] depthArray, int lineNum )
    {
        int count = 0;
        int[] threeSums = new int[lineNum-2];
        for( int i = 0; i < lineNum-2; i++ )
        {
            threeSums[i] = depthArray[i] + depthArray[i+1] + depthArray[i+2];
        }
        for( int i = 1; i < lineNum-2; i++ )
        {
            if( threeSums[i-1] < threeSums[i] )
            {
                ++count;
            }
        }
        System.out.println( "The count of three sums increase is " + count );


    }

}
