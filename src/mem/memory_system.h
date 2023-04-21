#ifndef MEMORY_SYSTEM_H
#define MEMORY_SYSTEM_H
class MemorySystem {
 public:
    virtual uint32_t* load(uint32_t addr, int whois_calling) = 0;
    virtual uint32_t* store(uint32_t addr, uint32_t data, int whois_calling) = 0;
    virtual void reset_delay() = 0;
};
#endif /* MEMORY_SYSTEM_H */
