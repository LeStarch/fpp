// ======================================================================
// \title  PassiveGuardedProducts.hpp
// \author [user name]
// \brief  hpp file for PassiveGuardedProducts component implementation class
// ======================================================================

#ifndef PassiveGuardedProducts_HPP
#define PassiveGuardedProducts_HPP

#include "PassiveGuardedProductsComponentAc.hpp"

class PassiveGuardedProducts :
  public PassiveGuardedProductsComponentBase
{

  public:

    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct PassiveGuardedProducts object
    PassiveGuardedProducts(
        const char* const compName //!< The component name
    );

    //! Destroy PassiveGuardedProducts object
    ~PassiveGuardedProducts();

  PRIVATE:

    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for noArgsGuarded
    //!
    //! A typed guarded input
    void noArgsGuarded_handler(
        FwIndexType portNum //!< The port number
    ) override;

    //! Handler implementation for noArgsReturnGuarded
    //!
    //! A typed guarded input
    U32 noArgsReturnGuarded_handler(
        FwIndexType portNum //!< The port number
    ) override;

    //! Handler implementation for noArgsReturnSync
    //!
    //! A typed sync input port
    U32 noArgsReturnSync_handler(
        FwIndexType portNum //!< The port number
    ) override;

    //! Handler implementation for noArgsSync
    //!
    //! A typed sync input port
    void noArgsSync_handler(
        FwIndexType portNum //!< The port number
    ) override;

    //! Handler implementation for typedGuarded
    //!
    //! A typed guarded input
    void typedGuarded_handler(
        FwIndexType portNum, //!< The port number
        U32 u32, //!< A U32
        F32 f32, //!< An F32
        bool b, //!< A boolean
        const Fw::StringBase& str1, //!< A string
        const E& e, //!< An enum
        const A& a, //!< An array
        const S& s //!< A struct
    ) override;

    //! Handler implementation for typedReturnGuarded
    //!
    //! A typed guarded input with a return type
    F32 typedReturnGuarded_handler(
        FwIndexType portNum, //!< The port number
        U32 u32, //!< A U32
        F32 f32, //!< An F32
        bool b, //!< A boolean
        const Fw::StringBase& str2, //!< A string
        const E& e, //!< An enum
        const A& a, //!< An array
        const S& s //!< A struct
    ) override;

    //! Handler implementation for typedReturnSync
    //!
    //! A typed sync input port with a return type
    F32 typedReturnSync_handler(
        FwIndexType portNum, //!< The port number
        U32 u32, //!< A U32
        F32 f32, //!< An F32
        bool b, //!< A boolean
        const Fw::StringBase& str2, //!< A string
        const E& e, //!< An enum
        const A& a, //!< An array
        const S& s //!< A struct
    ) override;

    //! Handler implementation for typedSync
    //!
    //! A typed sync input port
    void typedSync_handler(
        FwIndexType portNum, //!< The port number
        U32 u32, //!< A U32
        F32 f32, //!< An F32
        bool b, //!< A boolean
        const Fw::StringBase& str1, //!< A string
        const E& e, //!< An enum
        const A& a, //!< An array
        const S& s //!< A struct
    ) override;

  PRIVATE:

    // ----------------------------------------------------------------------
    // Handler implementations for data products
    // ----------------------------------------------------------------------

    //! Receive a container of type Container1
    void dpRecv_Container1_handler(
        DpContainer& container, //!< The container
        Fw::Success::T status //!< The container status
    ) override;

    //! Receive a container of type Container2
    void dpRecv_Container2_handler(
        DpContainer& container, //!< The container
        Fw::Success::T status //!< The container status
    ) override;

    //! Receive a container of type Container3
    void dpRecv_Container3_handler(
        DpContainer& container, //!< The container
        Fw::Success::T status //!< The container status
    ) override;

    //! Receive a container of type Container4
    void dpRecv_Container4_handler(
        DpContainer& container, //!< The container
        Fw::Success::T status //!< The container status
    ) override;

    //! Receive a container of type Container5
    void dpRecv_Container5_handler(
        DpContainer& container, //!< The container
        Fw::Success::T status //!< The container status
    ) override;

};

#endif
