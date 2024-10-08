#patch patches (come from openwrt/lede/target/linux/mediatek)
SRC_URI_append = " \
    file://0001-mtk-Revert-wifi-mt76-mt7996-fill-txd-by-host-driver.patch \
    file://0002-mtk-mt76-mt7996-use-hweight16-to-get-correct-tx_ant.patch \
    file://0003-mtk-mt76-mt7996-fix-MBSS.patch \
    file://0004-mtk-mt76-mt7996-fix-HE-and-EHT-phy-cap.patch \
    file://0005-mtk-mt76-mt7996-adjust-Beamformee-SS-capability.patch \
    file://0006-mtk-mt76-mt7996-add-support-for-IEEE-802.11-fragment.patch \
    file://0007-mtk-mt76-mt7996-set-rx-path-when-channel-switch.patch \
    file://0008-mtk-mt76-mt7996-set-station-s-wmm-index-to-3.patch \
    file://0009-mtk-mt76-mt7996-fix-rxd-checksum-offload-offset.patch \
    file://0010-mtk-mt76-mt7996-fix-EHT-Beamforming-capability-check.patch \
    file://0011-mtk-mt76-mt7996-fix-amsdu-information.patch \
    file://0012-mtk-mt76-mt7996-add-beacon_int_min_gcd-to-support-di.patch \
    file://0013-mtk-mt76-adjust-beamform-mcu-cmd-configuration-for-m.patch \
    file://0014-mtk-mt76-mt7996-add-preamble-puncture-support-for-mt.patch \
    file://0015-mtk-mt76-mt7996-add-driver-support-for-wpa3-ocv-and-.patch \
    file://0016-mtk-mt76-mt7996-enable-ser-query.patch \
    file://0017-mtk-mt76-mt7996-set-key-flag-IEEE80211_KEY_FLAG_GENE.patch \
    file://0018-mtk-mt76-mt7996-Fix-TGax-HE-4.51.1_24G-fail.patch \
    file://0019-mtk-mt76-mt7996-add-support-for-different-variants.patch \
    file://0020-mtk-mt76-mt7996-ACS-channel-time-too-long-on-duty-ch.patch \
    file://0021-mtk-mt76-mt7996-Fixed-null-pointer-dereference-issue.patch \
    file://0022-mtk-mt76-add-sanity-check-to-prevent-kernel-crash.patch \
    file://0023-mtk-mt76-mt7996-add-firmware-WA-s-coredump.patch \
    file://0024-mtk-mt76-mt7996-for-build-pass.patch \
    file://0025-mtk-mt76-mt7996-add-debug-tool.patch \
    file://0026-mtk-mt76-mt7996-add-check-for-hostapd-config-he_ldpc.patch \
    file://0027-mtk-mt76-mt7996-add-basic-testmode-support.patch \
    file://0028-mtk-mt76-mt7996-add-testmode-pre-calibration-support.patch \
    file://0029-mtk-mt76-mt7996-add-normal-mode-pre-calibration-supp.patch \
    file://0030-mtk-mt76-mt7996-enable-SCS-feature-for-mt7996-driver.patch \
    file://0031-mtk-mt76-mt7996-add-txpower-support.patch \
    file://0032-mtk-mt76-mt7996-add-binfile-mode-support.patch \
    file://0033-mtk-mt76-mt7996-add-testmode-ZWDFS-verification-supp.patch \
    file://0034-mtk-mt76-mt7996-support-eagle-ZWDFS-on-iFEM.patch \
    file://0035-mtk-mt76-mt7996-refactor-eeprom-loading-flow-for-sku.patch \
    file://0036-mtk-mt76-mt7996-add-vendor-commands-support.patch \
    file://0037-mtk-mt76-mt7996-add-debugfs-for-fw-coredump.patch \
    file://0038-mtk-mt76-mt7996-Add-mt7992-coredump-support.patch \
    file://0039-mtk-mt76-mt7996-add-support-for-runtime-set-in-band-.patch \
    file://0040-mtk-mt76-mt7996-add-support-spatial-reuse-debug-comm.patch \
    file://0041-mtk-mt76-mt7996-Establish-BA-in-VO-queue.patch \
    file://0042-mtk-mt76-mt7996-report-tx-and-rx-byte-to-tpt_led.patch \
    file://0043-mtk-mt76-mt7996-support-dup-wtbl.patch \
    file://0044-mtk-mt76-try-more-times-when-send-message-timeout.patch \
    file://0045-mtk-mt76-mt7996-add-SER-overlap-handle.patch \
    file://0046-mtk-mt76-mt7996-kite-default-1-pcie-setting.patch \
    file://0047-mtk-mt76-mt7996-support-BF-MIMO-debug-commands.patch \
    file://0048-mtk-mt76-mt7996-add-build-the-following-MURU-mcu-com.patch \
    file://0049-mtk-mt76-mt7996-add-cert-patch.patch \
    file://0050-mtk-mt76-mt7996-add-testmode-bf-support.patch \
    file://0051-mtk-mt76-mt7996-add-zwdfs-cert-mode.patch \
    file://0052-mtk-mt76-mt7996-add-channel-68-96.patch \
    file://0053-mtk-mt76-mt7996-add-kite-testmode-support.patch \
    file://0054-mtk-mt76-mt7996-assign-DEAUTH-to-ALTX-queue-for-CERT.patch \
    file://0055-mtk-mt76-mt7996-add-no_beacon-vendor-command-for-cer.patch \
    file://0056-mtk-mt76-mt7996-add-adie-efuse-merge-support.patch \
    file://0057-mtk-mt76-mt7996-add-Eagle-2adie-TBTC-BE14000-support.patch \
    file://0058-mtk-mt76-mt7996-add-background-radar-hw-cap-check.patch \
    file://0059-mtk-mt76-mt7996-add-fallback-in-case-of-missing-prec.patch \
    file://0060-mtk-mt76-mt7996-add-kite-part-number-support.patch \
    file://0061-mtk-wifi-mt76-revert-page_poll-for-kernel-5.4.patch \
    file://0062-mtk-mt76-rework-wed-rx-flow.patch \
    file://0063-mtk-mt76-change-wed-token-init-size-to-adapt-wed3.0.patch \
    file://0064-mtk-mt76-add-random-early-drop-support.patch \
    file://0065-mtk-mt76-mt7996-reset-addr_elem-when-delete-ba.patch \
    file://0066-mtk-mt76-change-pcie0-R5-to-pcie1-to-get-6G-ICS.patch \
    file://0067-mtk-mt76-add-SER-support-for-wed3.0.patch \
    file://0068-mtk-mt76-find-rx-token-by-physical-address.patch \
    file://0069-mtk-mt76-mt7996-add-dma-mask-limitation.patch \
    file://0070-mtk-mt76-mt7996-add-per-bss-statistic-info.patch \
    file://0071-mtk-mt76-mt7996-do-not-report-netdev-stats-on-monito.patch \
    file://0072-mtk-mt76-mt7996-add-support-for-HW-ATF.patch \
    file://0073-mtk-mt76-mt7996-add-SER0.5-support-w-wed3.0.patch \
    file://0074-mtk-mt76-mt7996-support-backaward-compatiable.patch \
    file://0075-mtk-mt76-mt7996-add-wed-support-for-mt7992.patch \
    file://0076-mtk-mt76-add-2pcie-one-wed-support.patch \
    file://0077-mtk-mt76-mt7996-Remove-wed-rro-ring-add-napi-at-init.patch \
    file://0078-mtk-mt76-mt7996-Remove-wed_stop-during-L1-SER.patch \
    file://0079-mtk-mt76-mt7996-Refactor-rro-del-ba-command-format.patch \
    file://0080-mtk-mt76-mt7996-get-airtime-and-RSSI-via-MCU-command.patch \
    file://0081-mtk-mt76-mt7996-add-support-for-WMM-PBC-configuratio.patch \
    file://0082-mtk-mt76-mt7996-eagle-support-extra-option_type.patch \
    file://0083-mtk-mt76-mt7996-support-enable-disable-thermal-prote.patch \
    file://0084-mtk-mt76-mt7996-support-thermal-recal-debug-command.patch \
    file://0085-mtk-mt76-mt7996-add-kite-two-pcie-with-two-wed-suppo.patch \
    file://0086-mtk-mt76-add-support-to-enable-index-FW-log-for-Cons.patch \
    file://0087-mtk-mt76-mt7996-implement-and-switch-to-hw-scan-call.patch \
    file://0088-mtk-mt76-mt7996-implement-and-switch-to-chanctx-call.patch \
    file://0089-mtk-mt76-mt7996-use-.sta_state-to-replace-.sta_add-a.patch \
    file://0090-mtk-mt76-mt7996-switch-to-per-link-data-structure-of.patch \
    file://0091-mtk-mt76-mt7996-switch-to-per-link-data-structure-of.patch \
    file://0092-mtk-mt76-extend-wcid-and-sta-flow-for-MLO-support.patch \
    file://0093-mtk-mt76-mt7996-enable-MLO-capability.patch \
    file://0094-mtk-mt76-mt7996-support-multi-link-vif-links-and-MLO.patch \
    file://0095-mtk-mt76-mt7996-support-multi-link-sta-links-and-MLO.patch \
    file://0096-mtk-mt76-mt7996-introduce-mt7996_band_phy-for-ch-ban.patch \
    file://0097-mtk-mt76-mt7996-rework-ieee80211_ops-callbacks-for-l.patch \
    file://0098-mtk-mt76-mt7996-rework-TXD-for-multi-link-support.patch \
    file://0099-mtk-mt76-mt7996-rework-TXS-for-multi-link-support.patch \
    file://0100-mtk-mt76-mt7996-rework-RXD-for-multi-link-support.patch \
    file://0101-mtk-mt76-mt7996-rework-mac-functions-for-multi-link-.patch \
    file://0102-mtk-mt76-rework-mcu-functions-for-multi-link-support.patch \
    file://0103-mtk-mt76-rework-connac-helpers.patch \
    file://0104-mtk-mt76-mt7996-handle-mapping-for-hw-and-phy.patch \
    file://0105-mtk-mt76-mt7996-handle-mapping-for-hw-and-vif.patch \
    file://0106-mtk-mt76-mt7996-rework-scanning-parts-for-MLD-STA-su.patch \
    file://0107-mtk-mt76-mt7996-implement-mld-address-translation.patch \
    file://0108-mtk-mt76-mt7996-use-BSS_CHANGED_TXPOWER-for-txpower-.patch \
    file://0109-mtk-mt76-mt7996-temp-support-for-single-wiphy.patch \
    file://0110-mtk-mt76-mt7996-implement-ieee80211_ops-for-link-deb.patch \
    file://0111-mtk-mt76-mt7996-support-multi-link-channel-switch.patch \
    file://0112-mtk-mt76-mt7996-ACS-channel-time-too-long-on-duty-ch.patch \
    file://0113-mtk-mt76-mt7996-add-beacon-monitoring-in-driver-for-.patch \
    file://0114-mtk-mt76-mt7996-support-band_idx-option-for-set_mu-g.patch \
    file://0115-mtk-mt76-mt7996-tmp-disable-VOW.patch \
    file://0116-mtk-mt76-mt7996-enable-ampdu-limit-to-avoid-BA-bound.patch \
    file://0117-mtk-mt76-mt7996-Fix-get_txpower-wrong-result-in-sing.patch \
    file://0118-mtk-mt76-mt7996-Add-connac3-csi-feature.patch \
    file://0119-mtk-mt76-mt7996-add-more-debug-info-for-MLO.patch \
    file://0120-mtk-mt76-add-internal-debug-tool.patch \
    file://0121-mtk-mt76-mt7996-add-linux-tracing-support.patch \
    file://0122-mtk-mt76-temp-changes-for-SQC-period.patch \
    file://0123-mtk-mt76-mt7996-remain-multiple-wiphy-model-for-test.patch \
    file://0124-mtk-mt76-mt7996-enable-ibf-capability-for-mt7992.patch \
    file://0125-mtk-mt76-remove-the-limitation-for-legacy-AP-sacn.patch \
    file://0126-mtk-mt76-add-support-for-get_survey-in-single-wiphy-.patch \
    file://0127-mtk-mt76-mt7996-add-critical-update-support.patch \
    file://0128-mtk-mt76-mt7996-Add-support-for-EMLSR.patch \
    file://0129-mtk-mt76-mt7996-add-max-mpdu-len-capability.patch \
    file://0130-mtk-mt76-mt7996-add-correct-bss_conf-for-legacy-AP-s.patch \
    file://0131-mtk-mt76-mt7996-fix-set-beacon-mcu-command.patch \
    file://0132-mtk-mt76-fix-incorrect-setting-of-antenna-capability.patch \
    file://0133-mtk-mt76-mt7996-fix-stop_tx_ba_session-warning.patch \
    file://0134-mtk-mt76-mt7996-do-software-link-addr-translation-fo.patch \
    file://0135-mtk-mt76-mt7996-add-per-band-debugfs-folder.patch \
    file://0136-mtk-mt76-mt7996-move-internal-debugfs-knob-to-per-ba.patch \
    file://0137-mtk-mt76-mt7996-refactor-amsdu-debugfs.patch \
    file://0138-mtk-mt76-mt7996-trigger-channel-calibration-for-DFS-.patch \
    file://0139-mtk-mt76-mt7996-do-not-remove-bss_info-and-starec-wh.patch \
    file://0140-mtk-mt76-mt7996-remove-chanctx-in-mt7996_bss_conf.patch \
    file://0141-mtk-mt76-mt7996-temporarily-disable-EPCS.patch \
    file://0142-mtk-mt76-mt7996-fix-kite-can-t-handle-11v-beacon-on-.patch \
    file://0143-mtk-mt76-mt7996-add-post-channel-switch-for-DFS-chan.patch \
    file://0144-mtk-mt76-mt7996-update-testmode-bf-support.patch \
    file://0145-mtk-mt76-mt7996-add-mlo-related-debugfs-knob.patch \
    file://0146-mtk-mt76-mt7996-add-debugfs-knob-to-show-mlo-related.patch \
    file://0147-mtk-mt76-mt7996-add-debugfs-knob-to-set-agc.patch \
    file://0148-mtk-mt76-mt7996-set-unused-band-to-UNSPECIFIED-in-ba.patch \
    file://0149-mtk-mt76-mt7996-support-per-link-report-of-bss-color.patch \
    file://0150-mtk-mt76-mt7996-Fix-inconsistent-QoS-mapping-between.patch \
    file://0151-mtk-mt76-mt7996-add-support-for-MLD-interface-to-sca.patch \
    file://0152-mtk-mt76-mt7996-add-per-link-txpower-config.patch \
    file://0153-mtk-mt76-mt7996-update-TX-RX-rates-via-MCU-command.patch \
    file://0154-mtk-mt76-mt7996-add-link-information-when-dump-stati.patch \
    file://0155-mtk-mt76-mt7996-add-per-link-RX-MPDU-statistics.patch \
    file://0156-mtk-mt76-mt7996-support-link_id-for-mt7996_set_bitra.patch \
    file://0157-mtk-mt76-mt7996-add-per-radio-antenna-config.patch \
    file://0158-mtk-mt76-mt7996-rework-debug-prints.patch \
    file://0159-mtk-mt76-mt7996-support-configure-trigger-frame-type.patch \
    file://0160-mtk-mt76-mt7996-support-configure-coding-type-for-wi.patch \
    file://0161-mtk-mt76-mt7996-record-RSSI-and-SNR.patch \
    file://0162-mtk-mt76-mt7996-support-find-the-mt7996_phy-by-link_.patch \
    file://0163-mtk-mt76-mt7996-workaround-for-get_tsf-crash-issue.patch \
    file://0164-mtk-mt76-add-debugfs-for-tx-drop-counters.patch \
    file://0165-mtk-mt76-add-debugfs-for-rx-drop-counters.patch \
    file://0166-mtk-mt76-mt7996-add-support-for-remain-on-channel-op.patch \
    file://0167-mtk-mt76-mt7996-rework-the-setting-flow-of-starec-RA.patch \
    file://0168-mtk-mt76-mt7996-Fix-NULL-pointer-crash-when-mac-tx-f.patch \
    file://0169-mtk-mt76-mt7996-update-adie-efuse-merge-support.patch \
    file://0170-mtk-mt76-mt7996-support-handle-link_id-in-ap_wireles.patch \
    file://0171-mtk-mt76-mt7996-fix-incorrect-indexing-of-MIB-FW-eve.patch \
    file://0172-mtk-mt76-mt7996-support-muru-dbg-info-debug-commands.patch \
    file://0173-mtk-mt76-mt7996-add-kite-if_comb.patch \
    file://0174-mtk-mt76-mt7996-change-source-of-per-WCID-TX-MPDU-st.patch \
    file://0175-mtk-mt76-mt7996-update-preamble-puncture-support-for.patch \
    file://0176-mtk-mt76-Add-dynamic-pp-vendor-and-debug-pp-algo-cmd.patch \
    file://0177-mtk-mt76-mt7996-disable-MAT-and-set-force-link-for-4.patch \
    file://0178-mtk-mt76-mt7996-add-per-STA-TX-MSDU-failed-and-retri.patch \
    file://0179-mtk-mt76-mt7996-fill-in-sn-into-txd-for-MLD-multicas.patch \
    file://0180-mtk-mt76-mt7996-fix-potential-null-pointer.patch \
    file://0181-mtk-mt76-mt7996-Fix-legacy-action-frame-wrong-addres.patch \
    file://0182-mtk-mt76-mt7996-add-AP-affiliated-link-removal-suppo.patch \
    file://0183-mtk-mt76-mt7996-add-support-for-AP-A-TTLM.patch \
    file://0184-mtk-mt76-mt7996-leave-ps-when-4-address-is-establish.patch \
    file://0185-mtk-mt76-mt7996-add-debugfs-knob-to-set-and-dump-txo.patch \
    file://0186-mtk-mt76-mt7996-add-mcu-command-to-set-bssid-mapping.patch \
    file://0187-mtk-mt76-mt7996-Temporary-fix-init-txpwoer-for-singl.patch \
    file://0188-mtk-mt76-mt7996-Add-lpi-support-with-sku_idx-and-enh.patch \
    file://0189-mtk-mt76-mt7996-Add-Triggered-Uplink-Access-Optimiza.patch \
    file://0190-mtk-mt76-mt7996-add-per-band-token-limit.patch \
    file://0191-mtk-mt76-sync-with-upstream-changes.patch \
    file://0192-mtk-mt76-mt7996-record-per-antenna-average-data-fram.patch \
    file://0193-mtk-mt76-mt7996-remove-default-bss_conf-when-link-be.patch \
    file://0194-mtk-mt76-mt7996-pass-vif-cfg.assoc-to-mt7996_mac_sta.patch \
    file://0195-mtk-mt76-mt7996-separate-hwrro-from-wed.patch \
    file://0196-mtk-mt76-mt7996-ignore-vif.dormant_links-in-mt7996_c.patch \
    file://0197-mtk-mt76-mt7996-add-Adv-TTLM-support-for-STA.patch \
    file://0198-mtk-mt76-mt7996-Add-AFC-and-lpi-power-support.patch \
    file://0199-mtk-mt76-do-not-report-ACK-when-TXS-is-lost.patch \
    "
