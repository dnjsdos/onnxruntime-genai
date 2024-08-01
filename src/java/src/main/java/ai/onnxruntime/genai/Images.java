package ai.onnxruntime.genai;

public final class Images implements AutoCloseable {
    private long nativeHandle = 0;

    public Images(String path) throws GenAIException {
        this.nativeHandle = loadImage(path);
    }

    public long open(String path) throws GenAIException {
        return loadImage(path);
    }    

    public long getNativeHandle() {
        return nativeHandle;
    }

    @Override
    public void close() throws Exception {        
        if (nativeHandle != 0) {
            destroyImage(nativeHandle);
            nativeHandle = 0;
        }
    }  

    private native long loadImage(String path) throws GenAIException;

    private native void destroyImage(long nativeHandle) throws GenAIException;
}
