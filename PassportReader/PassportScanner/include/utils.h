#ifndef PASSPORTSCANNER_UTILS_H
#define PASSPORTSCANNER_UTILS_H

#include <string>

namespace CardType{
    const int UNKNOWN = -1;                 //未知
    const int ID_CARD = 0;                  //二代证
    const int PASSPORT = 3;                 //护照         2行
    const int PASSPORT_WITHOUT_CHIP = 6;
    const int HKMO_EXIT_ENTRY_PERMIT = 2;        //港澳通行证    1行
    const int HK_MACAO_VISIT_MAINLAND = 4;  //回乡证，港澳居民来往内地通行证    3行; 这个会在processHXZJson里面再进行区分
    const int HK_VISIT_MAINLAND = 47;  //回乡证，港澳居民来往内地通行证    3行; 这个会在processHXZJson里面再进行区分
    const int MACAO_VISIT_MAINLAND = 48;  //回乡证，港澳居民来往内地通行证    3行; 这个会在processHXZJson里面再进行区分
    const int HK_MACAO_VISIT_MAINLAND_NOCHIP = 7;  //无芯片旧版回乡证，港澳居民来往内地通行证    3行
    const int TAIWAN_VISIT_MAINLAND = 49;     //台胞证，台湾居民来往大陆通行证   3行
    const int TAIWAN_PASSPORT = 5;            //台湾通行证    1行机读码
}

const int RET_SUCCESS = 0;
const int RET_FAILURE = -1;
const int RET_TIMEOUT = -2;
const int RET_BUSY = -3;
const int RET_CANCEL = -4;
const int RET_DEVICE_NOT_FOUND = -5;
const int RET_PERMISSION = -6;
const int RET_HARDWARE_ERR = -7;
const int RET_SCAN_FAILURE = -8;
const int RET_PARSE_FAILURE = -9;
const int RET_INVALID_MEDIA = -10;
const int RET_SCAN_TWICE = -11;
const int RET_SCAN_NON_ATOMIC = -12;
const int EVENT_TURN_OVER = 1;


const std::string NationTwoNationCodes[] = {
            "AF", "AX", "AL", "DZ", "AS", "AD", "AO", "AI", "AQ", "AG",
            "AR", "AM", "AW", "AU", "AT", "AZ", "BS", "BH", "BD", "BB",
            "BY", "BE", "BZ", "BJ", "BM", "BT", "BO", "BA", "BW", "BV",
            "BR", "IO", "BN", "BG", "BF", "BI", "KH", "CM", "CA", "CV",
            "KY", "CF", "TD", "CL", "CN", "CX", "CC", "CO", "KM", "CG",
            "CD", "CK", "CR", "CI", "HR", "CU", "CY", "CZ", "DK", "DJ",
            "DM", "DO", "EC", "EG", "SV", "GQ", "ER", "EE", "ET", "FK",
            "FO", "FJ", "FI", "FR", "GF", "PF", "TF", "GA", "GM", "GE",
            "DE", "GH", "GI", "GR", "GL", "GD", "GP", "GU", "GT", "GG",
            "GN", "GW", "GY", "HT", "HM", "VA", "HN", "HK", "HU", "IS",
            "IN", "ID", "IR", "IQ", "IE", "IM", "IL", "IT", "JM", "JP",
            "JE", "JO", "KZ", "KE", "KI", "KP", "KR", "KW", "KG", "LA",
            "LV", "LB", "LS", "LR", "LY", "LI", "LT", "LU", "MO", "MK",
            "MG", "MW", "MY", "MV", "ML", "MT", "MH", "MQ", "MR", "MU",
            "YT", "MX", "FM", "MD", "MC", "MN", "ME", "MS", "MA", "MZ",
            "MM", "NA", "NR", "NP", "NL", "AN", "NC", "NZ", "NI", "NE",
            "NG", "NU", "NF", "MP", "NO", "OM", "PK", "PW", "PS", "PA",
            "PG", "PY", "PE", "PH", "PN", "PL", "PT", "PR", "QA", "RE",
            "RO", "RU", "RW", "SH", "KN", "LC", "PM", "VC", "WS", "SM",
            "ST", "SA", "SN", "RS", "SC", "SL", "SG", "SK", "SI", "SB",
            "SO", "ZA", "GS", "ES", "LK", "SD", "SR", "SJ", "SZ", "SE",
            "CH", "SY", "TW", "TJ", "TZ", "TH", "TL", "TG", "TK", "TO",
            "TT", "TN", "TR", "TM", "TC", "TV", "UG", "UA", "AE", "GB", "GB", "GB", "GB", "GB", "GB",
            "US", "UM", "UY", "UZ", "VU", "VE", "VN", "VG", "VI", "WF",
            "EH", "YE", "ZM", "ZW", "ZZ", "ZZ", "BQ", "BL", "CW", "MF", "NT", "SS", "SX"
};

const std::string NationThreeNationCodes[] = {
            "AFG", "ALA", "ALB", "DZA", "ASM", "AND", "AGO", "AIA", "ATA", "ATG",
            "ARG", "ARM", "ABW", "AUS", "AUT", "AZE", "BHS", "BHR", "BGD", "BRB",
            "BLR", "BEL", "BLZ", "BEN", "BMU", "BTN", "BOL", "BIH", "BWA", "BVT",
            "BRA", "IOT", "BRN", "BGR", "BFA", "BDI", "KHM", "CMR", "CAN", "CPV",
            "CYM", "CAF", "TCD", "CHL", "CHN", "CXR", "CCK", "COL", "COM", "COG",
            "COD", "COK", "CRI", "CIV", "HRV", "CUB", "CYP", "CZE", "DNK", "DJI",
            "DMA", "DOM", "ECU", "EGY", "SLV", "GNQ", "ERI", "EST", "ETH", "FLK",
            "FRO", "FJI", "FIN", "FRA", "GUF", "PYF", "ATF", "GAB", "GMB", "GEO",
            "D", "GHA", "GIB", "GRC", "GRL", "GRD", "GLP", "GUM", "GTM", "GGY",
            "GIN", "GNB", "GUY", "HTI", "HMD", "VAT", "HND", "HKG", "HUN", "ISL",
            "IND", "IDN", "IRN", "IRQ", "IRL", "IMN", "ISR", "ITA", "JAM", "JPN",
            "JEY", "JOR", "KAZ", "KEN", "KIR", "PRK", "KOR", "KWT", "KGZ", "LAO",
            "LVA", "LBN", "LSO", "LBR", "LBY", "LIE", "LTU", "LUX", "MAC", "MKD",
            "MDG", "MWI", "MYS", "MDV", "MLI", "MLT", "MHL", "MTQ", "MRT", "MUS",
            "MYT", "MEX", "FSM", "MDA", "MCO", "MNG", "MNE", "MSR", "MAR", "MOZ",
            "MMR", "NAM", "NRU", "NPL", "NLD", "ANT", "NCL", "NZL", "NIC", "NER",
            "NGA", "NIU", "NFK", "MNP", "NOR", "OMN", "PAK", "PLW", "PSE", "PAN",
            "PNG", "PRY", "PER", "PHL", "PCN", "POL", "PRT", "PRI", "QAT", "REU",
            "ROU", "RUS", "RWA", "SHN", "KNA", "LCA", "SPM", "VCT", "WSM", "SMR",
            "STP", "SAU", "SEN", "SRB", "SYC", "SLE", "SGP", "SVK", "SVN", "SLB",
            "SOM", "ZAF", "SGS", "ESP", "LKA", "SDN", "SUR", "SJM", "SWZ", "SWE",
            "CHE", "SYR", "TWN", "TJK", "TZA", "THA", "TLS", "TGO", "TKL", "TON",
            "TTO", "TUN", "TUR", "TKM", "TCA", "TUV", "UGA", "UKR", "ARE", "GBR", "GBD", "GBN", "GBO", "GBP", "GBS",
            "USA", "UMI", "URY", "UZB", "VUT", "VEN", "VNM", "VGB", "VIR", "WLF",
            "ESH", "YEM", "ZMB", "ZWE", "UNO", "UNA", "BES", "BLM", "CUW", "MAF", "NTZ", "SSD", "SXM"
    };

const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

const int RECV_SIZE = 1000000;

void removeFile(const std::string& filePath);

bool removeDir(const std::string& szFileDir);

std::string getSFZImageURI(const std::string& workingFolder);

std::string getTwoNationCodes(std::string str);

std::string base64Encode(char const* bytes_to_encode, int in_len) ;
std::string base64Decode(std::string & encoded_string) ;

std::string getBase64Code(const std::string& picPath);

#endif