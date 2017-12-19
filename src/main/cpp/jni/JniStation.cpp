#include <jni.h>
#include "JniStation.h"
#include "../Station.h"
#include "JniString.h"

extern "C" {


JNIEXPORT jdouble JNICALL
Java_com_mxmariner_mxtide_internal_Station_latitude(JNIEnv *env,
                                                    jclass obj,
                                                    jlong ptr) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    return station->getLatitude();
}

JNIEXPORT jdouble JNICALL
Java_com_mxmariner_mxtide_internal_Station_longitude(JNIEnv *env,
                                                     jclass obj,
                                                     jlong ptr) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    return station->getLongitude();
}

JNIEXPORT jstring JNICALL
Java_com_mxmariner_mxtide_internal_Station_timeZone(JNIEnv *env,
                                                    jclass obj,
                                                    jlong ptr) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    auto timeZone = station->timeZone();
    return mdr::JniString::toJni(env, timeZone);
}

JNIEXPORT jstring JNICALL
Java_com_mxmariner_mxtide_internal_Station_name(JNIEnv *env,
                                                jclass obj,
                                                jlong ptr) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    auto name = station->name();
    return mdr::JniString::toJni(env, name);
}

JNIEXPORT jstring JNICALL
Java_com_mxmariner_mxtide_internal_Station_stationLocalTime(JNIEnv *env,
                                                            jclass obj,
                                                            jlong ptr,
                                                            jlong epoch) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    auto duration = std::chrono::duration<long long int>(epoch);
    TimePoint timePoint { duration };
    auto stamp = station->getTimeStamp(timePoint);
    return mdr::JniString::toJni(env, stamp);
}

JNIEXPORT jstring JNICALL
Java_com_mxmariner_mxtide_internal_Station_type(JNIEnv *env,
                                                jclass obj,
                                                jlong ptr) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    auto type = station->type().toString();
    return mdr::JniString::toJni(env, type);
}

JNIEXPORT void JNICALL
Java_com_mxmariner_mxtide_internal_Station_deleteStation(JNIEnv *env,
                                                         jclass obj,
                                                         jlong ptr) {
    mdr::Station *station = reinterpret_cast<mdr::Station *>(ptr);
    delete station;
}

}