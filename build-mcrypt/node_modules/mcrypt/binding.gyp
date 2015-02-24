{
    "targets": [
        {
            "target_name": "mcrypt",
            "sources": [
                "src/mcrypt.cc"
            ],
            "include_dirs": [
                "/usr/include/",
                "/opt/local/include/",
                "/usr/local/Cellar/mcrypt/"
            ],
            "link_settings": {
                "libraries": [
                    "-lmcrypt"
                ]
            }
        }
    ]
}
