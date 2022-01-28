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

        System.out.print( "{ " );
        for( int i = 0; i < pLineNum; i++ )
        {
            System.out.print( depthArray[i] + ", " );
        }
        System.out.println( " }" );
    }


}
