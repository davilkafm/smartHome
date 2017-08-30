
void logMessage(String message) {
    #ifdef DEBUG
    Serial.println(message);
    #endif
}

