find_path(
    OPENSSL_INCLUDE_DIR openssl/ec.h
    NAMES openssl/sha.h openssl/bn.h
    PATH_SUFFIXES include
    PATHS
    /usr/local/opt/openssl/           # if necessary, append your openssl path
    NO_DEFAULT_PATH
)
find_library(
    OPENSSL_LIBRARY libcrypto.a
    PATH_SUFFIXES lib
    PATHS
    /usr/local/opt/openssl/lib/           # if necessary, append your openssl path
    NO_DEFAULT_PATH
)
#set(OPENSSL_USE_STATIC_LIBS TRUE) 
set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl/" CACHE PATH "")
set(OPENSSL_ROOT_LIBRARIES "/usr/local/opt/openssl/lib/" CACHE PATH "")
#set(OPENSSL_CRYPTO_LIBRARY:FILEPATH=/usr/local/opt/openssl/lib/libcrypto.dylib)
set(OpenSSL_FOUND 1)

include_directories("/usr/local/opt/openssl/include")

find_package(Threads)
