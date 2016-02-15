<?php

/**
 * Returns $requirements array containing errors or success message
 * @param $version
 * @return mixed
 */
function easy_frames_check_version($version){
    $t = get_t();
    $library = libraries_detect('cropperjs');

    if (empty($library['installed'])) {
        $requirements['cropperjs'] = array(
            'title' => $t('Cropper js library'),
            'value' => $t('At least @a', array('@a' => $version)),
            'severity' => REQUIREMENT_ERROR,
            'description' =>
                $t('You need to download the !cropper, extract archive in /sites/all/libraries folder so there will be path like /sites/all/libraries/cropperjs/dist/cropper.min.js.',
                    array(
                        '!cropper' => l($t('Cropper plugin'), $library['download url']),
                        '%path' => 'sites/all/libraries',
                        '@js_file' => 'cropper.min.js',
                        '@css_file' => 'cropper.css',
                    )
                ),
        );
    }
    elseif (version_compare($library['version'], $version, '>=')) {
        $requirements['cropperjs'] = array(
            'title' => $t('Cropper js library found and installed correctly.'),
            'severity' => REQUIREMENT_OK,
            'value' => $library['version'],
        );
    }
    else {
        $requirements['cropperjs'] = array(
            'title' => $t('Cropper js library'),
            'value' => $t('At least @a', array('@a' => $version)),
            'severity' => REQUIREMENT_ERROR,
            'description' =>
                $t('You need to download a later version of the !cropper and replace the old version
            located in the %path directory on your server.',
                    array(
                        '!cropper' => l($t('Cropper plugin'), $library['download url']),
                        '%path' => $library['library path']
                    )
                ),
        );
    }
    return $requirements;
}