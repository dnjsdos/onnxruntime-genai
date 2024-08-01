package ai.onnxruntime.genai;


public class MultiModalProcessor implements AutoCloseable {
    private long nativeHandle = 0;    
    
    public MultiModalProcessor(long nativeHandle) throws GenAIException {
        this.nativeHandle = nativeHandle;
    }
    
    public NamedTensors processImageWithPrompt(String prompt, String imagePath) throws GenAIException, Exception {
        Images image = new Images(imagePath);

        if (nativeHandle == 0 || image.getNativeHandle() == 0) {
            image.close();
            throw new IllegalStateException("Processor has been freed and is invalid");
        }        

        NamedTensors inputTensor = new NamedTensors(processorProcessImage(nativeHandle, prompt, image.getNativeHandle()));
        image.close();

        return inputTensor;
    }

    public TokenizerStream createTokenizerStream() throws GenAIException {
        if (nativeHandle == 0) {
            throw new IllegalStateException("Instance has been freed and is invalid");
          }
      
        return new TokenizerStream(createTokenizerStreamFromProcessor(nativeHandle));
    }

    @Override
    public void close() throws Exception {        
        if (nativeHandle != 0) {
            destroyMultiModalProcessor(nativeHandle);
            nativeHandle = 0;
        }        
    }
    
    private native long processorProcessImage(long processorHandle, String prompt, long imageHandle) throws GenAIException;

    private native long createTokenizerStreamFromProcessor(long nativeHandle);

    private native void destroyMultiModalProcessor(long nativeHandle);
    
}
