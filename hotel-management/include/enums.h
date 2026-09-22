#ifndef ENUMS_H
#define ENUMS_H

// Enums for better type safety
enum class RoomType {
    SINGLE,
    DOUBLE,
    DELUXE,
    SUITE
};

enum class RoomStatus {
    AVAILABLE,
    OCCUPIED,
    MAINTENANCE,
    RESERVED
};

enum class BookingStatus {
    CONFIRMED,
    CHECKED_IN,
    CHECKED_OUT,
    CANCELLED
};

#endif // ENUMS_H