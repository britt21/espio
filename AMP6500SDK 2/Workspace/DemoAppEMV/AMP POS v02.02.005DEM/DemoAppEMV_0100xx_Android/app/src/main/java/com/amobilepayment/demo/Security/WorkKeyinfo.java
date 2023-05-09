package com.amobilepayment.demo.Security;

import com.pos.device.ped.KeySystem;
import com.pos.device.ped.KeyType;

/**
 * Created by Symbol Tabios on 25/09/2017.
 */

public class WorkKeyinfo {
    private int masterKeyIndex ;
    private int workKeyIndex ;
    private KeySystem keySystem ;
    private KeyType keyType ;
    private byte[] hexKeyData ;
    private int mode ;

    public int getMasterKeyIndex() {
        return masterKeyIndex;
    }

    public void setMasterKeyIndex(int masterKeyIndex) {
        this.masterKeyIndex = masterKeyIndex;
    }

    public int getWorkKeyIndex() {
        return workKeyIndex;
    }

    public void setWorkKeyIndex(int workKeyIndex) {
        this.workKeyIndex = workKeyIndex;
    }

    public KeySystem getKeySystem() {
        return keySystem;
    }

    public void setKeySystem(KeySystem keySystem) {
        this.keySystem = keySystem;
    }

    public KeyType getKeyType() {
        return keyType;
    }

    public void setKeyType(KeyType keyType) {
        this.keyType = keyType;
    }

    public byte[] getPrivacyKeyData() {
        return hexKeyData;
    }

    public void setPrivacyKeyData(byte[] privacyKeyData) {
        this.hexKeyData = privacyKeyData;
    }

    public int getMode() {
        return mode;
    }

    public void setMode(int mode) {
        this.mode = mode;
    }
}
