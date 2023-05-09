package com.amobilepayment.demo.service;

import android.os.Message;

// Interface needed by listening activities
public interface BaseChannelListener {
        // for list of codes, please refer to BaseChannelContract class
        void onServerReply(Message msg);
        void onServerReply(int msg);
}
