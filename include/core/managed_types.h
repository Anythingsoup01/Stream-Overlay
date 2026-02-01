#pragma once

struct ChatMessageBuffer
{
public:
    ~ChatMessageBuffer()
    {
        Release();
    }

    void Allocate(uint64_t maxUsernameSize, uint64_t maxMessageSize)
    {
        free(UsernameData);
        UsernameData = nullptr;
        UsernameSize = maxUsernameSize;

        free(MessageData);
        MessageData = nullptr;
        MessageSize = maxMessageSize;

        if (maxUsernameSize == 0 || maxMessageSize == 0)
            return;

        UsernameData = new char[maxUsernameSize];
        MessageData = new char[maxMessageSize];
    }

    void Reset(const char* userName, const char* message) {
        size_t userLen = strlen(userName);
        size_t messageLen = strlen(message);

        if (userLen == 0 || messageLen == 0)
            return;

        SO_ASSERT(userLen <= UsernameSize, "Username Buffer Overflow!");
        SO_ASSERT(messageLen <= MessageSize, "Message Buffer Overflow!");

        memcpy(&UsernameData, &userName, userLen);
        memcpy(&MessageData, &message, messageLen);
    }

    const char* username() const { return UsernameData ? UsernameData : ""; }
    const char* message() const { return MessageData ? MessageData : ""; }

private:

    void Release()
    {
        UsernameData = nullptr;
        UsernameSize = 0;

        MessageData = nullptr;
        MessageSize = 0;
    }

private:
    char* UsernameData = nullptr;
    char* MessageData = nullptr;
    uint64_t UsernameSize = 0;
    uint64_t MessageSize = 0;
    bool Updated = false;
};
