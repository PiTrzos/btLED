package com.example.rgbcontroller.data

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import com.example.rgbcontroller.data.model.DeviceEntity
import com.example.rgbcontroller.data.model.FavColorEntity

@Database(
    entities = [FavColorEntity::class],
    version = 1,
)

abstract class FavColorDatabase : RoomDatabase(){
    abstract val colors: FavColorDAOInterface
    companion object{
        fun open(context: Context): FavColorDatabase = Room.databaseBuilder(
            context,
            FavColorDatabase::class.java,
            "colors.db"
        ).build()
    }
}