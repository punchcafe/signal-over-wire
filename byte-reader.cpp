#define HIGHVOLT 1
#define LOWVOLT 0

#define INDEX1 0x01
#define INDEX2 0x03
#define INDEX3 0b01

#include <stdio.h>
#include <assert.h> 


class ByteReader
{
    public:

    void reset(){
        this->byteResult = 0x00;
        this->byteloadIndex = 0;
    }

    int getIntValue()
    {
        return (int) this->byteResult;
    }

    char getCharValue()
    {
        return (char) this->byteResult;
    }

    bool readBit(bool isHigh)
    {
        if(this->byteloadIndex >= 7)
        {
            return false;
        }

        if(isHigh)
        {
            unsigned char currentChar = this->getCharForIndex(this->byteloadIndex);
            this->byteResult = this->byteResult | currentChar;
        }
        this->byteloadIndex++;
        if(this->byteloadIndex >= 7){
            return false;
        } else {
            return true;
        }
    }

    private:
    unsigned char byteResult;
    short byteloadIndex;

    unsigned char getCharForIndex(int index){
        // Return the char  coresponding to a single 1 at that index, i.e.:
        // getCharForIndex(2) -> 0b00000100
        assert(index >= 0);
        unsigned int roof = 0b10000000;
        int timesToFloorDivide = 7 - index;
        for(int i = 0; i < timesToFloorDivide; i++){
            roof = roof/2;
        }
        return roof;
    }


};

int main()
{
    // testing functionality
    ByteReader br = ByteReader();
    // 0b0000101 -> the number 5
    br.reset();
    br.readBit(true);
    br.readBit(false);
    br.readBit(true);
    // printf("%d", br.getIntValue());
    printf("%d", br.getIntValue()));

    // 0b1100011 -> the character 'c'
    br.reset();
    br.readBit(true);
    br.readBit(true);
    br.readBit(false);
    br.readBit(false);
    br.readBit(false);
    bool hasMore1 = br.readBit(true);
    bool hasMore2 = br.readBit(true);
    assert(hasMore1);
    assert(!hasMore2);
    printf("%c", br.getCharValue());

}