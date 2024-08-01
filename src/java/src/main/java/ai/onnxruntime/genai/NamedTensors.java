package ai.onnxruntime.genai;

public class NamedTensors {
    private long nativeHandle = 0;

    public NamedTensors(long nativeHandle) {
        this.nativeHandle = nativeHandle;
    }

    public long getNativeHandle() {
        return nativeHandle;
    }
}
