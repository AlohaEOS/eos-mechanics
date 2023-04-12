#include "eosmechanics.hpp"

namespace benchmark
{
   // private functions
   BOOL eosmechanics::is_prime(int p)
   {
      if (p == 2)
      {
         return TRUE;
      }
      else if (p <= 1 || p % 2 == 0)
      {
         return FALSE;
      }

      BOOL prime = TRUE;
      const int to = sqrt(p);
      int i;
      for (i = 3; i <= to; i += 2)
      {
         if (!((prime = BOOL(p)) % i))
            break;
      }
      return prime;
   }

   BOOL eosmechanics::is_mersenne_prime(int p)
   {
      if (p == 2)
         return TRUE;

      const long long unsigned m_p = (1LLU << p) - 1;
      long long unsigned s = 4;
      int i;
      for (i = 3; i <= p; i++)
      {
         s = (s * s - 2) % m_p;
      }
      return BOOL(s == 0);
   }

   // public functions
   void eosmechanics::cpu()
   {
      require_auth(get_self());

      int p;

      for (p = 2; p <= CPU_PRIME_MAX; p += 1)
      {
         if (is_prime(p) && is_mersenne_prime(p))
         {
         }
      }
   }

   void eosmechanics::ram()
   {
      require_auth(get_self());

      ramdata_index ramdata(get_self(), get_self().value);

      size_t i;

      // Write
      for (i = 0; i < RAM_ROWS_MAX; i++)
      {
         ramdata.emplace(get_self(), [&](auto &row)
                         {
                    row.id = i;
                    row.one = "testing"; });
      }

      // Read
      for (const auto &row : ramdata)
      {
         i = row.id;
      }

      // Delete
      for (auto itr = ramdata.begin(); itr != ramdata.end();)
      {
         itr = ramdata.erase(itr);
      }
   }

   void eosmechanics::net(std::string input)
   {
      require_auth(get_self());
   }
}

EOSIO_DISPATCH(benchmark::eosmechanics, (cpu)(ram)(net))