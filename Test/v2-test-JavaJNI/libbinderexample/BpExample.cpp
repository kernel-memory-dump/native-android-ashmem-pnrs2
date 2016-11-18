#define LOG_NDEBUG 0
#define LOG_TAG "BpExample"

#include <cutils/log.h>
#include <binder/Parcel.h>

#include "BpExample.h"

using namespace android;


BpExample::BpExample(const sp<IBinder>& impl) :
	BpInterface<IExample>(impl)
{

}

int32_t BpExample::getExample()
{
    Parcel data, reply;
    int32_t example;

    ALOGV("%s enter", __FUNCTION__);
    // sta je ovo koji kurac
    // InterfaceDescriptor koji servis treba da se pogodi XD
    // LOLOLOLOLOL
    // ^______^ 
    //                    X____________X

    //     *___*
    // 

    data.writeInterfaceToken(IExample::getInterfaceDescriptor());
    
     // transact, KOJU FUNKCIJU ZELIMO DA POGODIMO, KOJE PODATKE SALJEMO, GDE HOCEMO POVRATNU VREDNOIST
    remote()->transact(GET_EXAMPLE, data, &reply);
    //////////  B L O K I R A J U C A -- FU N K CI J A AJAJAJAJAJJA
    /// / / / / /  C EK AMO DOK NE ODRAID SERVIS SVOJE
    // 
    reply.readInt32();  // ovo znamo vec sta je KEK
    reply.readInt32(&example);    // PO  VRRATNA VREDNOSTOTOTOTOTOT
    // reply.readInt64

    ALOGV("%s exit", __FUNCTION__);
    // AKO VRACA VISE OD JEDNE STVARI, NPR STAVIMO  STRUKTURU NEKU OP OP 
    return example;
}


int32_t BpExample::setExample(int32_t argument)
{
    Parcel data, reply;
    int32_t example;

    ALOGV("%s enter", __FUNCTION__);
    // sta je ovo koji kurac
    // InterfaceDescriptor koji servis treba da se pogodi XD
    // LOLOLOLOLOL
    // ^______^ 
    //                    X____________X

    //     *___*
    // 

    data.writeInterfaceToken(IExample::getInterfaceDescriptor());
    
    data.writeInt32(argument);

     // transact, KOJU FUNKCIJU ZELIMO DA POGODIMO, KOJE PODATKE SALJEMO, GDE HOCEMO POVRATNU VREDNOIST
    remote()->transact(SET_EXAMPLE, data, &reply);
    //////////  B L O K I R A J U C A -- FU N K CI J A AJAJAJAJAJJA
    /// / / / / /  C EK AMO DOK NE ODRAID SERVIS SVOJE
    // 
    reply.readInt32();  // ovo znamo vec sta je KEK
    reply.readInt32(&example);    // PO  VRRATNA VREDNOSTOTOTOTOTOT
    // reply.readInt64

    ALOGV("%s exit", __FUNCTION__);
    // AKO VRACA VISE OD JEDNE STVARI, NPR STAVIMO  STRUKTURU NEKU OP OP 
    return example;
}

void BpExample::registerCallback(sp<INativeCallback> callback)
{
        Parcel data, reply;
        ALOGV("%s enter", __FUNCTION__);

        data.writeInterfaceToken(IExample::getInterfaceDescriptor());

        

        
        data.writeStrongBinder(INativeCallback::asBinder(callback));
        
        remote()->transact(REGISTER_CALLBACK, data, &reply);
        reply.readInt32();

        ALOGV("%s exit", __FUNCTION__);

}



