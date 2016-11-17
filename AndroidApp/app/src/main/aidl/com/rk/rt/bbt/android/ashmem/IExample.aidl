// IExample.aidl
package com.rk.rt.bbt.android.ashmem;
import com.rk.rt.bbt.android.ashmem.INativeCallback;

interface IExample {

     int getExample();
     void setExample(int value);
     void registerCallback(INativeCallback callback);
}
