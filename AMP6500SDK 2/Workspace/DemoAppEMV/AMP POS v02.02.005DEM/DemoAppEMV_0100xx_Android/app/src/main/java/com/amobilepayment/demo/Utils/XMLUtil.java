package com.amobilepayment.demo.Utils;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.DocumentHelper;
import org.dom4j.Node;
import org.dom4j.io.SAXReader;

import java.io.InputStream;

public class XMLUtil {

    public static Node parseString(String stringXML) {
        Node node = null;
        try {
            Document document = DocumentHelper.parseText(stringXML);
            node = document.getRootElement();
        } catch (DocumentException e) {
            e.printStackTrace();
        }
        return node;
    }

    public static Node parseFile(InputStream is) {
        Node retData = null;
        SAXReader xmlReader = new SAXReader();
        try {
            Document document = xmlReader.read(is);
            retData = document.getRootElement();
        } catch (DocumentException e) {
            e.printStackTrace();
        }

        return retData;
    }
}
