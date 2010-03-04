/*
* ECDSA
* (C) 2007 Falko Strenzke, FlexSecure GmbH
*          Manuel Hartl, FlexSecure GmbH
* (C) 2008-2010 Jack Lloyd
*
* Distributed under the terms of the Botan license
*/

#ifndef BOTAN_ECDSA_KEY_H__
#define BOTAN_ECDSA_KEY_H__

#include <botan/ecc_key.h>

namespace Botan {

/**
* This class represents ECDSA Public Keys.
*/
class BOTAN_DLL ECDSA_PublicKey : public virtual EC_PublicKey,
                                  public PK_Verifying_wo_MR_Key
   {
   public:

      /**
      * Construct a public key from a given public point.
      * @param dom_par the domain parameters associated with this key
      * @param public_point the public point defining this key
      */
      ECDSA_PublicKey(const EC_Domain_Params& dom_par,
                      const PointGFp& public_point) :
         EC_PublicKey(dom_par, public_point) {}

      ECDSA_PublicKey(const AlgorithmIdentifier& alg_id,
                      const MemoryRegion<byte>& key_bits) :
         EC_PublicKey(alg_id, key_bits) {}

      /**
      * Get this keys algorithm name.
      * @result this keys algorithm name ("ECDSA")
      */
      std::string algo_name() const { return "ECDSA"; }

      /**
      * Get the maximum number of bits allowed to be fed to this key.
      * This is the bitlength of the order of the base point.
      * @result the maximum number of input bits
      */
      u32bit max_input_bits() const { return domain().get_order().bits(); }

      u32bit message_parts() const { return 2; }

      u32bit message_part_size() const
         { return domain().get_order().bytes(); }

      /**
      * Verify a message with this key.
      * @param message the byte array containing the message
      * @param mess_len the number of bytes in the message byte array
      * @param signature the byte array containing the signature
      * @param sig_len the number of bytes in the signature byte array
      */
      bool verify(const byte message[], u32bit mess_len,
                  const byte signature[], u32bit sig_len) const;

   protected:
      ECDSA_PublicKey() {}
   };

/**
* This class represents ECDSA Private Keys
*/
class BOTAN_DLL ECDSA_PrivateKey : public ECDSA_PublicKey,
                                   public EC_PrivateKey,
                                   public PK_Signing_Key
   {
   public:
      /**
      * Default constructor. Use this one if you want to later fill
      * this object with data from an encoded key.
      */
      ECDSA_PrivateKey() {}

      /**
      * Generate a new private key
      * @param the domain parameters to used for this key
      */
      ECDSA_PrivateKey(RandomNumberGenerator& rng,
                       const EC_Domain_Params& domain) :
         EC_PrivateKey(rng, domain) {}

      /**
      * Load a private key
      * @param domain parameters
      * @param x the private key
      */
      ECDSA_PrivateKey(const EC_Domain_Params& domain, const BigInt& x) :
         EC_PrivateKey(domain, x) {}

      /**
      * Sign a message with this key.
      * @param message the byte array representing the message to be signed
      * @param mess_len the length of the message byte array
      * @result the signature
      */

      SecureVector<byte> sign(const byte message[], u32bit mess_len,
                              RandomNumberGenerator& rng) const;
   };

}

#endif
