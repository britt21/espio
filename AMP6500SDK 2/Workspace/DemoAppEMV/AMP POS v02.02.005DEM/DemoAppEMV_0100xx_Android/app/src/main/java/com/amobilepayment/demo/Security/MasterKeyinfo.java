package com.amobilepayment.demo.Security;


import com.pos.device.ped.KeySystem;
import com.pos.device.ped.KeyType;

/**
 * Created by Symbol Tabios on 25/09/2017.
 */

public class MasterKeyinfo {
    private int masterIndex ;
    private KeyType keyType ;
    private byte[] plainKeyData ;
    private KeySystem keySystem ;

    public int getMasterIndex() {
        return masterIndex;
    }

    public void setMasterIndex(int masterIndex) {
        this.masterIndex = masterIndex;
    }

    public KeyType getKeyType() {
        return keyType;
    }

    public void setKeyType(KeyType keyType) {
        this.keyType = keyType;
    }

    public byte[] getPlainKeyData() {
        return plainKeyData;
    }

    public void setPlainKeyData(byte[] plainKeyData) {
        this.plainKeyData = plainKeyData;
    }

    public KeySystem getKeySystem() {
        return keySystem;
    }

    public void setKeySystem(KeySystem keySystem) {
        this.keySystem = keySystem;
    }
}
