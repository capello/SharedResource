/// \file
/// \brief Manage unit class
/// \author Anthony Jaguenaud
/// \version v0.0
///
/// The unit class is used to add unit to a numeric type.

namespace Share {
  /// \brief Unit class.
  template<class Type> class Unit
  {
  public:
    /// \brief Unable units.
    enum UnitValues {
      ABSOLUTE, ///< Absolute unit. For a set of 75 elements, 50\<ABSOLUTE\> means 50 elements.
      PERCENTS  ///< Percent unit. For a set of 75 elements, 50\<PERCENTS\> means 37 elements (not 38).
    };
    /// \brief Constructor.
    Unit();
    /// \brief Destructor.
    virtual ~Unit();
  };
};
