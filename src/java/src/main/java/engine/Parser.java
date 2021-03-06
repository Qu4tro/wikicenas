package engine;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.util.List;

public class Parser {
    public static void parse(List<String> filenames, Result result){
        Handler handler = new Handler(result);
        for(String filename: filenames) {
            try {
                File inputFile = new File(filename);

                SAXParserFactory factory = SAXParserFactory.newInstance();
                SAXParser saxParser = factory.newSAXParser();
                InputStream inputStream= new FileInputStream(inputFile);
                Reader isr = new InputStreamReader(inputStream,"UTF-8");
                
              
                InputSource is = new InputSource(isr);
                is.setEncoding("utf-8");
                saxParser.parse(is, handler);

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}

enum ParserState {
    PAGE, PAGE_ID, PAGE_TITLE, PAGE_TEXT,
    REVISION, REVISION_ID, REVISION_TIMESTAMP,
    CONTRIBUTOR_ID, CONTRIBUTOR_USERNAME,
    NOWHERE
}

class Handler extends DefaultHandler {

    private StringBuilder characters;
    private ParserState state;
    private Result result;

    private Long page_id;
    private String page_title;
    private Long revision_id;
    private String revision_timestamp;
    private Long contributor_id;
    private String contributor_username;

    private long nBytes, nWords;
    private boolean inWord;

    public Handler(Result r){
        characters = new StringBuilder();
        result = r;
        inWord = false;
        nBytes = 0;
        nWords = 0;
    }

    @Override
    public void startElement(String uri, String ln, String elemName, Attributes attr) throws SAXException {
        switch (elemName){
            case "id":
                switch (state){
                    case PAGE_TITLE:
                        state = ParserState.PAGE_ID;
                        break;
                    case PAGE_ID:
                        state = ParserState.REVISION_ID;
                        break;
                    case CONTRIBUTOR_USERNAME:
                        state = ParserState.CONTRIBUTOR_ID;
                        break;
                }
                break;
            case "username":
                state = ParserState.CONTRIBUTOR_USERNAME;
                break;
            case "title":
                state = ParserState.PAGE_TITLE;
                break;
            case "timestamp":
                state = ParserState.REVISION_TIMESTAMP;
                break;
            case "text":
                state = ParserState.PAGE_TEXT;
                nBytes = 0;
                nWords = 0;
                break;
        }
    }

    @Override
    public void endElement(String uri, String ln, String elemName) throws SAXException {
        final String content = characters.toString().trim();
        switch (elemName){
            case "id":
                switch (state){
                    case PAGE_ID:
                        page_id = Long.parseLong(content);

                        break;
                    case REVISION_ID:
                        revision_id = Long.parseLong(content);
                     
                        break;
                    case CONTRIBUTOR_ID:
                        contributor_id = Long.parseLong(content);
                   
                        break;
                }
                break;

            case "title":
                page_title = content;
                break;

            case "timestamp":
                revision_timestamp = content;
                break;

            case "username":
                contributor_username = content;
                break;

            case "text":
            	inWord=false;
                result.addPage(page_id, page_title, nBytes, nWords);
                break;

            case "revision":
                result.addRevision(revision_id, revision_timestamp);
                break;

            case "contributor":
                result.addContributor(contributor_id, revision_id, contributor_username);
                break;
        }
        characters.setLength(0);

    }

    private boolean space(char c){
        return (c == ' ' || c == '\n' || c == '\t');
    }

    @Override
    public void characters(char ch[], int start, int length) throws SAXException {
    	String str = new String(ch, start, length);
        if (state == ParserState.PAGE_TEXT) {
            try {
				nBytes +=  str.getBytes("UTF-8").length;
			
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			};
           
			
			for (int i = 0; i < length; i++) {
                if (!inWord && !space(ch[start + i])) {
                    inWord = true;
                    nWords += 1;
                }
                if (inWord && space(ch[start + i])) {
                    inWord = false;
                }
            }
        } else {
            
            characters.append(str);
        }
    }
}
