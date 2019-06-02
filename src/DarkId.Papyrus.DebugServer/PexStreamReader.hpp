#pragma once

#include <cstdint>
#include <ctime>
#include <fstream>

#include "Champollion/Pex/Binary.hpp"

namespace Pex {

/**
 * @brief Binary structure file reading.
 *
 * The PexStreamReader class provides a function to read a PEX file into a Binary structure.
 * The filename is provided as a parameter of the constructor.
 */
class PexStreamReader
{
public:
    PexStreamReader(std::istream* stream);
    ~PexStreamReader();

    void read(Binary& binary);
	void readHeader(Header& header);

protected:
    void read(StringTable& stringTable);
    void read(DebugInfo& debugInfo);
    void read(UserFlags& userFlags);
    void read(Objects& objects);
    void read(StructInfos& structInfos);
    void read(Variables& variables);
    void read(Properties& properties);
    void read(States& states);
    void read(Functions& functions);
    void read(Function& function);
    void read(TypedNames& typednames);
    void read(Instructions& instructions);


    std::uint8_t getUint8();
    std::uint16_t getUint16();
    std::uint32_t getUint32();
    StringTable::Index getStringIndex();

    std::int16_t getInt16();
    float getFloat();
    std::time_t getTime();
    std::string getString();
    Value getValue();

    const StringTable* m_StringTable;

private:
    std::istream *m_Stream;
};
}
