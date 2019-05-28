#include <jni.h>
#include <string>

int index() {
    return 2;
}

void bar() {
    int a[2] = {1, 0};
    int b=a[index()];
}

void foo() {
    bar();
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_asantest_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */)
{
    std::string hello = "Hello from C++";
    foo();
    return env->NewStringUTF(hello.c_str());
}
