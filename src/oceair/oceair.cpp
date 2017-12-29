#include <erl_nif.h>
#include "stdio.h"

#include <stdarg.h>
#include <time.h>

#include "oceair.h"

#include "QtCore"
#include "QJsonObject"

#define LOG_FILE_PATH "/var/log/oceiot/mqtt_oceair.log"

#ifdef __cplusplus
extern "C" {
#endif

QByteArray myba;

static const char *mqttMessageRecordNameTable[] = {
    "mqtt_message",
    "id",        ///< binary() | undefined
    "pktid",     ///< 1..16#ffff | undefined
    "from",      ///< atom() | {binary(), undefined | binary()}
    "topic",     ///< binary()
    "qos",       ///< 0 | 1 | 2
    "flags",     ///< [retain | dup | sys]
    "retain",    ///< boolean()
    "dup",       ///< boolean()
    "sys",       ///< boolean()
    "headers",   ///< list()
    "payload",   ///< binary()
    "timestamp", ///< erlang:timestamp()
    NULL
};

int write_log(const char *format, ...) {
    static FILE* pLogFile = NULL;
    va_list arg;
    int done;

    if (pLogFile == NULL) {
        pLogFile = fopen(LOG_FILE_PATH, "a");
    }

    va_start (arg, format);

    time_t time_log = time(NULL);
    struct tm* tm_log = localtime(&time_log);
    fprintf(pLogFile, "[%04d-%02d-%02d %02d:%02d:%02d]", tm_log->tm_year + 1900, tm_log->tm_mon + 1, tm_log->tm_mday, tm_log->tm_hour, tm_log->tm_min, tm_log->tm_sec);

    done = vfprintf(pLogFile, format, arg);

    va_end (arg);


    fprintf(pLogFile, "\r\n");

    fflush(pLogFile);

    return done;
}


static ERL_NIF_TERM on_client_connected(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    write_log("call on_client_connected");
    return enif_make_string(env, "OK", ERL_NIF_LATIN1);
}

static ERL_NIF_TERM on_client_disconnected(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    write_log("call on_client_disconnected");
    return enif_make_string(env, "OK", ERL_NIF_LATIN1);
}

static ERL_NIF_TERM on_client_subscribe(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    write_log("call on_client_subscribe");
    return enif_make_string(env, "OK", ERL_NIF_LATIN1);
}

static ERL_NIF_TERM on_client_unsubscribe(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    write_log("call on_client_unsubscribe");
    return enif_make_string(env, "OK", ERL_NIF_LATIN1);
}

int messageMemberName2Index(const char *name)
{
    int i;
    if (name == NULL) {
        return -1;
    }

    for (i = 0; mqttMessageRecordNameTable[i] != NULL; i++) {
        if (strcmp(name, mqttMessageRecordNameTable[i]) == 0) {
            return i;
        }
    }
    return -1;
}

static ERL_NIF_TERM on_message_publish(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    char buf[200];
    int i;
    int len;
    QJsonObject json;
    ERL_NIF_TERM *terms;
    enif_get_tuple(env, argv[0], &len, (const ERL_NIF_TERM **)&terms);
    write_log("call on_message_publish, %d elements in the message tuple", len);

    json["a"] = QJsonValue("b");

    for (i = 0; i < len; i++) {
        if (mqttMessageRecordNameTable[i] == NULL) {
            break;
        }
        enif_snprintf(buf, 200, "%s = %T",
                      mqttMessageRecordNameTable[i], terms[i]);
        write_log("%s", buf);
    }

    return argv[0];
}

static ERL_NIF_TERM on_message_delivered(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    write_log("call on_message_delivered");
    return enif_make_string(env, "OK", ERL_NIF_LATIN1);
}

static ERL_NIF_TERM on_message_acked(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    write_log("call on_message_acked");
    return enif_make_string(env, "OK", ERL_NIF_LATIN1);
}

static ErlNifFunc nif_funcs[] =
{
    {"on_client_connected", 1, on_client_connected},
    {"on_client_disconnected", 2, on_client_disconnected},
    {"on_client_subscribe", 3, on_client_subscribe},
    {"on_client_unsubscribe", 3, on_client_unsubscribe},
    {"on_message_publish", 1, on_message_publish},
    {"on_message_delivered", 3, on_message_delivered},
    {"on_message_acked", 3, on_message_acked},
};

ERL_NIF_INIT(oceair, nif_funcs,NULL,NULL,NULL,NULL)

#ifdef __cplusplus
}
#endif

