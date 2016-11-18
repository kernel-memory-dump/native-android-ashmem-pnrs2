class BpNativeServiceClient : public BpInterface<INativeService>
{

public:

    BpExample(const sp<IBinder>& impl);
    virtual void registerCallback(sp<INativeCallback> callback) = 0;

};