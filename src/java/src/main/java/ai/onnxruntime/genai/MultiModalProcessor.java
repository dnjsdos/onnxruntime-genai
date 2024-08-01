package ai.onnxruntime.genai;

public class MultiModalProcessor implements AutoCloseable {
    private long nativeHandle = 0;    

    public MultiModalProcessor(Model model) {        
    }

    @Override
    public void close() throws Exception {        
        if (nativeHandle != 0) {
            destroyMultiModalProcessor(nativeHandle);
            nativeHandle = 0;
          }
    }

    private native void destroyMultiModalProcessor(long nativeHandle);
    
}
