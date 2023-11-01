package com.example.rgbcontroller.data.model

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "color")
data class FavColorEntity (
    @PrimaryKey(autoGenerate = true)
    val id: Long = 0,
    val RGBstr: String,
    val color: Int
)