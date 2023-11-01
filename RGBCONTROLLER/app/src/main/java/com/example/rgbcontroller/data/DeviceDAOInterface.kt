package com.example.rgbcontroller.data

import androidx.room.*
import com.example.rgbcontroller.data.model.DeviceEntity
import com.example.rgbcontroller.data.model.FavColorEntity

@Dao
interface DeviceDAOInterface {
    @Query("SELECT * FROM device;")
    fun getAllDevices(): List<DeviceEntity>
    @Insert
    fun addDevice(newDevice: DeviceEntity)
    @Update
    fun updateDevice(device: DeviceEntity)
    @Query("DELETE FROM device WHERE name = :identity;")
    fun deleteDeviceById(identity: String)
}