package com.example.rgbcontroller.models

import androidx.annotation.DrawableRes

data class Device(
    val name: String,
    val note: String,
    val connected: String,
    @DrawableRes
    val resId: Int
)
