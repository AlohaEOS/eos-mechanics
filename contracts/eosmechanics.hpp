#include <eosio/eosio.hpp>
#include <math.h>

#pragma precision = log10l(ULLONG_MAX) / 2
typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOL;

// Max when calculating primes in cpu test
#define CPU_PRIME_MAX 375

// Number of rows to write/read in ram test
#define RAM_ROWS_MAX 75

namespace benchmark
{
    struct [[eosio::table]] ramdata
    {
        uint64_t id;
        std::string one;

        auto primary_key() const { return id; }
        EOSLIB_SERIALIZE(ramdata, (id)(one))
    };
    using ramdata_index = eosio::multi_index<"ramdata"_n, ramdata>;

    class [[eosio::contract("eosmechanics")]] eosmechanics : public eosio::contract
    {
    private:
        BOOL is_prime(int p);
        BOOL is_mersenne_prime(int p);

    public:
        using contract::contract;

        /**
         * Simple CPU benchmark that calculates Mersenne prime numbers.
         */
        [[eosio::action]] void cpu();

        /**
         * Simple EOS RAM benchmark which reads and writes a table.
         */
        [[eosio::action]] void ram();

        /**
         * Simple EOS Net benchmark which just accepts any string passed in.
         */
        [[eosio::action]] void net(std::string input);
    };
}