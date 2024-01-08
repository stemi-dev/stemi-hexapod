int _version = 2;

int getVersion() {
    return _version;
}

void setVersion(int v) {
    _version = v;
}

bool isV1() {
    return _version == 1;
}

bool isV2() {
    return _version == 2;
}