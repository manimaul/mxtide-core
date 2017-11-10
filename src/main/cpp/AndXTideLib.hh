/*
 * AndXTideLib.hh
 *
 *  Created on: Mar 28, 2013
 *  Author: Will Kamp - manimaul@gmail.com
 */

#ifndef ANDXTIDELIB_HH_
#define ANDXTIDELIB_HH_


#include <time.h>
#include <xtide/libxtide.hh>
#include <jni.h>
#include <android/log.h>
#include <string.h>

using namespace libxtide;
using namespace std;

extern "C" {
JNIEXPORT void JNICALL Java_com_mxmariner_andxtidelib_XtideJni_loadHarmonics( JNIEnv *env, jobject obj, jstring pPath );
JNIEXPORT void JNICALL Java_com_mxmariner_andxtidelib_XtideJni_setUnits( JNIEnv *env, jobject obj, jint pUnit );
JNIEXPORT jobjectArray JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationIndex( JNIEnv *env, jobject obj );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationAbout( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationRawData( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationPlainData( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationPrediction( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationTimestamp( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationClockSvg( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
JNIEXPORT jstring JNICALL Java_com_mxmariner_andxtidelib_XtideJni_getStationGraphSvg( JNIEnv *env, jobject obj, jstring pStationName, jlong pEpoch );
}



void loadHarmonics(const char* path);
void getAbout(Dstr station, long epoch);
void getClock(Dstr station, long epoch);
void getGraph(Dstr station, long epoch);
void getPrediction(Dstr station, long epoch);
void getData(Dstr station, long epoch, Mode::Mode mode);
jobjectArray getStationIndex(JNIEnv *env);
void getTimestamp(Dstr station, long epoch);

#endif /* ANDXTIDELIB_HH_ */
