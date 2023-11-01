package com.example.rgbcontroller.data

import androidx.room.*
import com.example.rgbcontroller.data.model.FavColorEntity

@Dao
interface FavColorDAOInterface {
    @Query("SELECT * FROM color;")
    fun getAllColors(): List<FavColorEntity>
    @Insert
    fun addColor(newColor: FavColorEntity)
    @Update
    fun updateColor(color: FavColorEntity)
    @Query("DELETE FROM color WHERE RGBstr = :identity;")
    fun deleteColorById(identity: String)
}