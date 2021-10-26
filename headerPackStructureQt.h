/**
 * Developed By Muhammad Almuhmmah
 * Year : 2021
 * Freeware File
 *
Smart Pack Structure For QC Diag And LG LAF Commands 
 - High flexibility in use
 - Easy and expandable without the usual limits
 - It can easily be expanded to support other protocols
 - It automatically generates the value CRC X25
 - Flexibility in arguments is limitless
 C++ Qt
 **/
-------------------------------------------------------------------------
#define getMemoryDataHex(x) QByteArray((const char*)&x,sizeof(x)).toHex()
typedef struct __arg_item__{
    __arg_item__(const QVariant &variant,const QString &name){
        Variant=variant;
        Name=name;
    }
    QVariant Variant;
    QString Name;
}ArgItem;
#ifdef LAF_STRUCTURE
template<typename ... Args>
static QByteArray PackStructureLaf(const Args&... args) // At least one argument
{
    QD(endl<<endl<<"------------------                    PackLafStructure 2               ------------------");
    QList<ArgItem> lv;
    int sink[] = { 0, ((void)(lv.append(ArgItem(args,QString::fromStdString(type_name<decltype(args)>())))), 0)... };(void) sink;
    bool bls=1;
    QVariant vArg;
    QByteArray output;
    int type=0;
    for(int i=0;i<lv.count();i++)
    {
        ArgItem item=lv.at(i);
        vArg=item.Variant;
        //        qDebug() <<item.Name<<vArg<<output;
        type=(int)(QMetaType::Type)vArg.type();
        if(type==QMetaType::Type::UInt or type==QMetaType::Type::Double or type==QVariant::Int or type==QVariant::LongLong or type==QVariant::ULongLong){
            if(item.Name=="unsigned char const&"){
                unsigned char const carVl=vArg.toChar().toLatin1();
                output.append(getMemoryDataHex(carVl));
            }else if(item.Name=="short const&" or item.Name=="unsigned short const&"){
                short shortVl=vArg.toInt();
                output.append(getMemoryDataHex(shortVl));
            }else if(type==QMetaType::Type::Double){
                double NumberVl=vArg.toDouble();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::Int){
                int NumberVl=vArg.toInt();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::UInt){
                uint NumberVl=vArg.toUInt();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::LongLong){
                qlonglong NumberVl=vArg.toLongLong();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::ULongLong){
                qulonglong NumberVl=vArg.toULongLong();
                output.append(getMemoryDataHex(NumberVl));
            }
        }else if(type==QVariant::String){
            output.append(vArg.toString());
        }else if(type==QVariant::Char)
            output.append(vArg.toChar());
        else if(type==QVariant::ByteArray)
            output.append(vArg.toByteArray());
    }
   // calculate crc x25
    if(output.length()>=32){
        QByteArray ddd=QByteArray::fromHex(output);
        quint16 crc=qChecksum(ddd.data(),ddd.length());
        output.clear();
        output=ddd.mid(0,24);
        output.append((char*)&crc,sizeof(crc));
        output.append(QByteArray().fill(0x0,2));
        output.append(ddd.mid(28));
        output=output.toHex();
    }
    if(output.length()>=300){
        bls=0;
    }
    if(bls)
        qDebug() <<"output[HEX]"<<output.toUpper();
    output=QByteArray::fromHex(output);
    if(bls)
        qDebug() <<"output"<<output;
    return output;
}
template<typename ... Args>
static QByteArray PackStructureQC(const Args&... args) // At least one argument
{
    QD(endl<<endl<<"------------------                    PackStructureQC                ------------------");
    QList<ArgItem> lv;
    int sink[] = { 0, ((void)(lv.append(ArgItem(args,QString::fromStdString(type_name<decltype(args)>())))), 0)... };(void) sink;
    bool bls=1;
    QVariant vArg;
    QByteArray output;
    int type=0;
    for(int i=0;i<lv.count();i++)
    {
        ArgItem item=lv.at(i);
        vArg=item.Variant;
        type=(int)(QMetaType::Type)vArg.type();
        if(type==QMetaType::Type::UInt or type==QMetaType::Type::Double or type==QVariant::Int or type==QVariant::LongLong or type==QVariant::ULongLong){
            if(item.Name=="unsigned char const&"){
                unsigned char const carVl=vArg.toChar().toLatin1();
                output.append(getMemoryDataHex(carVl));
            }else if(item.Name=="short const&" or item.Name=="unsigned short const&"){
                short shortVl=vArg.toInt();
                output.append(getMemoryDataHex(shortVl));
            }else if(type==QMetaType::Type::Double){
                double NumberVl=vArg.toDouble();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::Int){
                int NumberVl=vArg.toInt();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::UInt){
                uint NumberVl=vArg.toUInt();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::LongLong){
                qlonglong NumberVl=vArg.toLongLong();
                output.append(getMemoryDataHex(NumberVl));
            }else if(type==QMetaType::Type::ULongLong){
                qulonglong NumberVl=vArg.toULongLong();
                output.append(getMemoryDataHex(NumberVl));
            }
        }else if(type==QVariant::String){
            output.append(vArg.toString());
        }else if(type==QVariant::Char)
            output.append(vArg.toChar());
        else if(type==QVariant::ByteArray)
            output.append(vArg.toByteArray());
    }
    // calculate crc x25
    if(output.length()>=2){
        QByteArray ddd=QByteArray::fromHex(output);
        quint16 crc=qChecksum(ddd.data(),ddd.length());
        output.clear();
        output=ddd;
        output.append((char*)&crc,sizeof(crc));
        output.append(0x7E);
        output=output.toHex();
    }
    qDebug() <<"output[HEX] QC "<<output.toUpper();
    output=QByteArray::fromHex(output);
    return output;
}
#define QC_FILL(len)                       QByteArray().fill('0',len*2)
#define QC_STANDARD_FILL(len)              QByteArray().fill('0',len)
//-----------------------------------------------------------------------
PackStructureQC(uint8_t(0xFA),
                          uint8_t(0xC3),
                          QC_FILL(34));
PackStructureLaf(LAF_CMD_HELO,
                            LAF_DEFAULT_VERSION,
                            LAF_FILL(20), // +4 for include crc space
                            LAF_MAGIC(LAF_CMD_HELO));
